#ifndef HELPSCENE_H
#define HELPSCENE_H

#include "Base/basescene.h"

class HelpScene : public BaseScene
{
public:
    HelpScene();

    // BaseScene interface
public:
    virtual void Init() override;
    virtual void Render() override;
    virtual void KeyPressEvent(QKeyEvent *event) override;
    virtual void KeyReleaseEvent(QKeyEvent *event) override;

private:

    std::shared_ptr<Billboard> m_Keys;
};

#endif // HELPSCENE_H
