#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "base/basescene.h"

class MainScene : public BaseScene
{
public:
    MainScene();
    ~MainScene() override;
    virtual void Init() override;
    virtual void Render() override;
    void KeyPressEvent(QKeyEvent *event) override;
    void KeyReleaseEvent(QKeyEvent *event) override;
private:

    std::shared_ptr<Billboard> m_Play;
    std::shared_ptr<Billboard> m_Help;
    std::shared_ptr<Billboard> m_ActiveBillboard;
};

#endif // MAINSCENE_H
