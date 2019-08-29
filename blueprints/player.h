#ifndef PLAYER_H
#define PLAYER_H

#include "math/jbamath.h"
#include <memory>
#include "objects/sphere.h"

class PlaneXY;
class Shader;
class Sphere;
class QKeyEvent;
class Player
{
public:
    Player(std::shared_ptr<Sphere> mObject, float MovementSpeed=0.1f);

    void Init();
    void Tick(std::shared_ptr<PlaneXY> Plane=nullptr);

    std::shared_ptr<Sphere> GetPlayerObject() const { return PlayerObject; }


    void KeyPressEvent(QKeyEvent *event);
    void KeyReleaseEvent(QKeyEvent *event);

    void SetPosition(jba::Vector3D Position) {PlayerObject->m_Transform.Position = Position;}

    void SetMovementSpeed(float MovementSpeed=0.05f) { m_MovementSpeed = MovementSpeed; }


    bool bIsColliding{false};
    float m_MovementSpeed = 0.05f;
    jba::Vector3D m_Velocity{};
private:
    void MoveForward(int Direction);
    void MoveRight(int Direction);

    void CalculatePlayerY(std::shared_ptr<PlaneXY> Plane);

    std::shared_ptr<Sphere> PlayerObject;


    bool wIsPressed = false;
    bool aIsPressed = false;
    bool sIsPressed = false;
    bool dIsPressed = false;


    jba::Vector3D m_Acceleration{};
};

#endif // PLAYER_H
