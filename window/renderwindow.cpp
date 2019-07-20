#include "renderwindow.h"
#include <QTimer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>
#include <QtMath>
#include "cmath"
#include "mainwindow.h"

#include "Scenes/allscenes.h"
#include "Managers/scenemanager.h"

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : m_Context(nullptr), m_Initialized(false), m_MainWindow(mainWindow)

{
    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    m_Context = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    m_Context->setFormat(requestedFormat());
    if (!m_Context->create())
    {
        delete m_Context;
        m_Context = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }
    m_RenderTimer = new QTimer(this);
}
void RenderWindow::CalculateGlobalCenter()
{
    m_GlobalCenter = mapToGlobal(QPoint(width()/2, height()/2));
    if(!b_AltIsPressed)
    {

        setCursor(Qt::BlankCursor);

        if(b_FirstMouse)
        {
            QCursor::setPos(m_GlobalCenter);
            b_FirstMouse = false;
        }

        float xPos = QCursor::pos().x();
        float yPos = QCursor::pos().y();

        float xOffset = xPos - m_GlobalCenter.x();
        float yOffset = m_GlobalCenter.y() - yPos;
        QCursor::setPos(m_GlobalCenter);

        SceneManager::GetInstance()->GetCurrentScene()->GetActiveCamera()->UpdateRotation(xOffset, yOffset);
    }
}

void RenderWindow::Init()
{

    //********************** General OpenGL stuff **********************

    //The OpenGL context has to be set. The context belongs to the instanse of this class!
    if (!m_Context->makeCurrent(this))
    {
        qDebug() << "makeCurrent() failed";
        return;
    }

    //Just to make sure we don't init several times
    if (!m_Initialized)
        m_Initialized = true;

    initializeOpenGLFunctions();

    startOpenGLDebugger();
    glEnable(GL_DEPTH_TEST);    //enables depth sorting - must use GL_DEPTH_BUFFER_BIT in glClear
    glEnable(GL_CULL_FACE);     //draws only front side of models - usually what you want -

    glClearColor(0.4f, 0.4f, 0.4f,1.0f);    //Color used in glClear GL_COLOR_BUFFER_BIT

    //****************** My Stuff *****************



    //Connects Signals/Slots
    connect(m_RenderTimer, SIGNAL(timeout()), this, SLOT(Render()));
    connect(m_MainWindow, &MainWindow::onActionWireframeTriggered, this, &RenderWindow::ToggleWireframe);

    mProjectionMatrix = std::make_shared<jba::Matrix4x4>();

    SceneManager::GetInstance()->GetCurrentScene();

    CalculateGlobalCenter();
}
void RenderWindow::Render()
{
    m_TimeStart.restart(); //restart FPS clock
    m_Context->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)
    initializeOpenGLFunctions();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //to clear the screen for each redraw

    //********************** Render OpenGL stuff **********************
    SceneManager::GetInstance()->GetCurrentScene()->Render();

    CalculateGlobalCenter();
    UpdateProjectionMatrix();

    //checkForGLerrors(); // OpenGL Debugger

    m_Context->swapBuffers(this);
}

void RenderWindow::UpdateProjectionMatrix()
{
    //Calculate ProjectionMatrix
    const qreal retinaScale = devicePixelRatio();
    double w = width() * retinaScale;
    double h = height() * retinaScale;
    mProjectionMatrix->perspective(SceneManager::GetInstance()->GetCurrentScene()->GetActiveCamera()->GetZoom(),static_cast<float>(w/h),0.1f, 10000.f);

    for(auto& Shader : ShaderManager::GetInstance()->GetShaders())
    {
        Shader->use();
        Shader->setMat4("ProjectionMatrix", mProjectionMatrix->constData());
    }
}

void RenderWindow::exposeEvent(QExposeEvent *)
{
    if (!m_Initialized)
        Init();

    //This is just to support modern screens with "double" pixels
    const qreal retinaScale = devicePixelRatio();
    double w = width() * retinaScale;
    double h = height() * retinaScale;
    glViewport(0, 0, static_cast<GLint>(w), static_cast<GLint>(h));

    if (isExposed())
    {
        m_RenderTimer->start(16); //16 means 16ms = 60 Frames pr second
        m_TimeStart.start();
    }
}


void RenderWindow::calculateFramerate()
{
    long long nsecElapsed = m_TimeStart.nsecsElapsed();
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (m_MainWindow)    //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30) //once pr 30 frames = update the message twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            m_MainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                   QString::number(static_cast<double>(nsecElapsed/1000000.f), 'g', 4) + " ms  |  " +
                                                   "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 60 frames
        }
    }
}

void RenderWindow::checkForGLerrors()
{
    if(m_OpenGLDebugLogger)
    {
        const QList<QOpenGLDebugMessage> messages = m_OpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            if(message.severity() == QOpenGLDebugMessage::Severity::HighSeverity)
                qDebug() << message;
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
            qDebug() << "glGetError returns " << err;
    }
}
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (!format.testOption(QSurfaceFormat::DebugContext))
            qDebug() << "This system can not use QOpenGLDebugLogger, so we revert to glGetError()";

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            m_OpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (m_OpenGLDebugLogger->initialize()) // initializes in the current context
                qDebug() << "Started OpenGL debug logger!";
        }
    }
}
void RenderWindow::ToggleWireframe(bool isChecked)
{
    if(isChecked)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
}

void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    SceneManager::GetInstance()->GetCurrentScene()->KeyPressEvent(event);

    if(event->key() == Qt::Key_8)
    {
        auto list = SceneManager::GetInstance()->GetCurrentScene()->GetCameras();
        auto size = SceneManager::GetInstance()->GetCurrentScene()->GetCameras().size();
        auto id = SceneManager::GetInstance()->GetCurrentScene()->GetActiveCameraID();
        id++;
        if(id > size -1 )
            id = 0;
        SceneManager::GetInstance()->GetCurrentScene()->SetActiveCameraID(id);
        SceneManager::GetInstance()->GetCurrentScene()->SetActiveCamera(list.at(id));
    }
    if(event->key() == Qt::Key_Alt)
    {
        b_AltIsPressed = !b_AltIsPressed;
        setCursor(Qt::ArrowCursor);
    }
}

void RenderWindow::keyReleaseEvent(QKeyEvent *event)
{
    SceneManager::GetInstance()->GetCurrentScene()->KeyReleaseEvent(event);
}

void RenderWindow::wheelEvent(QWheelEvent *event)
{
    SceneManager::GetInstance()->GetCurrentScene()->GetActiveCamera()->KeyScrollEvent(event);
}
