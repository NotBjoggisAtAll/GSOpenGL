#ifndef LIGHTSCENE_H
#define LIGHTSCENE_H

#include "base/basescene.h"

class BaseCube;
class PlaneXY;
class Player;

class LightScene : public BaseScene
{
public:
    LightScene();
    ~LightScene() override;
    virtual void Init() override;
    virtual void Render() override;
    virtual void KeyPressEvent(QKeyEvent *event) override;
    virtual void KeyReleaseEvent(QKeyEvent *event) override;

private:
    std::shared_ptr<PlaneXY> m_Plane;
    std::shared_ptr<Player> m_Player;
};

#endif // LIGHTSCENE_H
