#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSurfaceFormat>
#include <QDebug>
#include "renderwindow.h"
#include "Managers/scenemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
}

void MainWindow::Init()
{
    //This will contain the setup of the OpenGL surface we will render into
    QSurfaceFormat format;

    //OpenGL v 4.1 - (Ole Flatens Mac does not support higher than this...)
    //you can try other versions, but then have to update RenderWindow and Shader
    //to inherit from other than QOpenGLFunctions_4_1_Core
    format.setVersion(4, 1);
    //Using the main profile for OpenGL - no legacy code permitted
    format.setProfile(QSurfaceFormat::CoreProfile);
    //A QSurface can be other types that OpenGL
    format.setRenderableType(QSurfaceFormat::OpenGL);

    //This should activate OpenGL debug Context used in RenderWindow::startOpenGLDebugger().
    //This line (and the startOpenGLDebugger() and checkForGLerrors() in RenderWindow class)
    //can be deleted, but it is nice to have OpenGL debug info!
    format.setOption(QSurfaceFormat::DebugContext);


    format.setSamples(4);
    // The renderer will need a depth buffer - (not requiered to set in glfw-tutorials)
    format.setDepthBufferSize(24);

    //Just prints out what OpenGL format we will get
    // - this can be deleted
    qDebug() << "Requesting surface format: " << format;

    //We have a format for the OpenGL window, so let's make it:
    m_RenderWindow = std::make_unique<RenderWindow>(format, this);

    //Check if renderwindow did initialize, else prints error and quit
    if (!m_RenderWindow->context())
    {
        qDebug() << "Failed to create context. Can not continue. Quits application!";
        return;
    }

    //The OpenGL RenderWindow got made, so continuing the setup:
    //We put the RenderWindow inside a QWidget so we can put in into a
    //layout that is made in the .ui-file
    m_RenderWindowContainer = QWidget::createWindowContainer(m_RenderWindow.get());
    //OpenGLLayout is made in the .ui-file!
    ui->OpenGLLayout->addWidget(m_RenderWindowContainer);

    //sets the keyboard input focus to the RenderWindow when program starts
    // - can be deleted, but then you have to click inside the renderwindow to get the focus
    m_RenderWindowContainer->setFocus();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionBoxScene_triggered()
{
    ui->actionBoxScene->setChecked(true);
    ui->actionHouseScene->setChecked(false);
    ui->actionBezierScene->setChecked(false);
    ui->actionLightScene->setChecked(false);
    ui->actionOblig3Scene->setChecked(false);

    SceneManager::GetInstance()->LoadScene(ESceneName::EMain);
}

void MainWindow::on_actionHouseScene_triggered()
{
    ui->actionHouseScene->setChecked(true);
    ui->actionBoxScene->setChecked(false);
    ui->actionBezierScene->setChecked(false);
    ui->actionLightScene->setChecked(false);
    ui->actionOblig3Scene->setChecked(false);

    SceneManager::GetInstance()->LoadScene(ESceneName::EHouse);

}

void MainWindow::on_actionBezierScene_triggered()
{
    ui->actionBezierScene->setChecked(true);
    ui->actionHouseScene->setChecked(false);
    ui->actionBoxScene->setChecked(false);
    ui->actionLightScene->setChecked(false);
    ui->actionOblig3Scene->setChecked(false);

    SceneManager::GetInstance()->LoadScene(ESceneName::EBezier);

}

void MainWindow::on_actionWireframe_triggered()
{
    emit onActionWireframeTriggered(ui->actionWireframe->isChecked());
}


void MainWindow::on_actionLightScene_triggered()
{
    ui->actionBezierScene->setChecked(false);
    ui->actionHouseScene->setChecked(false);
    ui->actionBoxScene->setChecked(false);
    ui->actionLightScene->setChecked(true);
    ui->actionOblig3Scene->setChecked(false);

    SceneManager::GetInstance()->LoadScene(ESceneName::ELight);
}

void MainWindow::on_actionOblig3Scene_triggered()
{
    ui->actionBezierScene->setChecked(false);
    ui->actionHouseScene->setChecked(false);
    ui->actionBoxScene->setChecked(false);
    ui->actionLightScene->setChecked(false);
    ui->actionOblig3Scene->setChecked(true);

    SceneManager::GetInstance()->LoadScene(ESceneName::EOblig3);
}

void MainWindow::on_actionAxis_triggered()
{
    auto scene = SceneManager::GetInstance()->GetCurrentScene();
    if(scene->GetAxis()->m_IsDead)
    {
        scene->GetAxis()->m_IsDead = false;
        ui->actionAxis->setChecked(false);

    }
    else
    {
        scene->GetAxis()->m_IsDead = true;
        ui->actionAxis->setChecked(true);
    }

}

void MainWindow::on_actionPause_triggered()
{
    auto scene = SceneManager::GetInstance()->GetCurrentScene();
    if(scene->IsPaused())
    {
        scene->SetPaused(false);
        ui->actionPause->setChecked(false);
    }
    else
    {
        scene->SetPaused(true);
        ui->actionPause->setChecked(true);
    }

}

void MainWindow::on_actionRestart_triggered()
{
    SceneManager::GetInstance()->RestartScene();
}

void MainWindow::on_actionHelp_triggered()
{
    SceneManager::GetInstance()->LoadScene(ESceneName::EHelp);
}
