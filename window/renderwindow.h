#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>
#include <memory>
#include "Math/jbamath.h"

class QOpenGLDebugLogger;
class QOpenGLContext;
class MainWindow;

class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
    //**************** DEFUALT STUFF ***************
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    QOpenGLContext *context() { return m_Context; }


private slots:
    void Render();

private:
    void Init();
    void exposeEvent(QExposeEvent *) override;

    QOpenGLContext *m_Context{nullptr};
    bool m_Initialized{false};
    QTimer *m_RenderTimer;     //timer that drives the gameloop
    QElapsedTimer m_TimeStart;       //time variable that reads the actual FPS
    QOpenGLDebugLogger *m_OpenGLDebugLogger{nullptr};
    MainWindow *m_MainWindow;    //points back to MainWindow to be able to put info in StatusBar

    void checkForGLerrors();

    void calculateFramerate();

    void startOpenGLDebugger();

    //******************* MY STUFF *********************

public slots:
    void ToggleWireframe(bool isChecked);

private:

    void UpdateProjectionMatrix();
    std::shared_ptr<jba::Matrix4x4> mProjectionMatrix;


    void CalculateGlobalCenter();
    bool b_FirstMouse{true};
    bool b_AltIsPressed{false};
    QPoint m_GlobalCenter{};

protected:

    //**************** KeyEvene Stuff ************
    //void mousePressEvent(QMouseEvent *event) override{}
    //void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // RENDERWINDOW_H
