#ifndef HOUSESCENE_H
#define HOUSESCENE_H

#include "Base/basescene.h"

class Axis;
class Player;
class Object;
class PlaneXY;
class HouseScene : public BaseScene
{
public:
    HouseScene();
    ~HouseScene() override;
    virtual void Init() override;
    virtual void Render() override;

    virtual void KeyPressEvent(QKeyEvent* event) override;
    virtual void KeyReleaseEvent(QKeyEvent* event) override;

protected:
    std::shared_ptr<BaseCube> m_Cube;
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<Object> m_Car;
};

#endif // HOUSESCENE_H
