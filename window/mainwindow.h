#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class QWidget;
class RenderWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void onActionWireframeTriggered(bool);

private slots:

    void on_actionExit_triggered();

    void on_actionBoxScene_triggered();

    void on_actionHouseScene_triggered();

    void on_actionWireframe_triggered();

    void on_actionBezierScene_triggered();

    void on_actionLightScene_triggered();

    void on_actionOblig3Scene_triggered();

    void on_actionAxis_triggered();

    void on_actionPause_triggered();

    void on_actionRestart_triggered();

    void on_actionHelp_triggered();

private:
    void Init();
    Ui::MainWindow *ui;

    QWidget *m_RenderWindowContainer{};
    std::unique_ptr<RenderWindow> m_RenderWindow;
};

#endif // MAINWINDOW_H
