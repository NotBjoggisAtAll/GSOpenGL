#include "player.h"
#include "QKeyEvent"
#include "Objects/sphere.h"
#include "Shaders/shader.h"
#include "Objects/planexy.h"
#include <QDebug>

Player::Player(std::shared_ptr<Sphere> Object, float MovementSpeed) : PlayerObject(Object), m_MovementSpeed(MovementSpeed) {}

void Player::Init()
{}

void Player::Tick(std::shared_ptr<PlaneXY> Plane)
{
    if(wIsPressed)
        m_Acceleration = {1,0,0};

    if(sIsPressed)
        m_Acceleration = {-1,0,0};

    if(aIsPressed)
        m_Acceleration = {0,0,-1};

    if(dIsPressed)
        m_Acceleration = {0,0,1};

    m_Acceleration.normalize();
    m_Velocity += m_Acceleration;
    m_Acceleration = {};
    SetPosition(GetPosition() + (m_Velocity * m_MovementSpeed));
    m_Velocity = m_Velocity * (1 - 0.2f);

    if(Plane)
        CalculatePlayerY(Plane);

    PlayerObject->SetPosition(GetPosition());
    PlayerObject->SetRotation(getRotation());



}
void Player::KeyPressEvent(QKeyEvent* event)
{

    if(event->key() == Qt::Key_Up)
    {
        wIsPressed = true;
    }
    if(event->key() == Qt::Key_Down)
    {
        sIsPressed = true;
    }
    if(event->key() == Qt::Key_Left)
    {
        aIsPressed = true;
    }
    if(event->key() == Qt::Key_Right)
    {
        dIsPressed = true;
    }

}
void Player::KeyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Up)
    {
        wIsPressed = false;
    }
    if(event->key() == Qt::Key_Down)
    {
        sIsPressed = false;
    }
    if(event->key() == Qt::Key_Left)
    {
        aIsPressed = false;
    }
    if(event->key() == Qt::Key_Right)
    {
        dIsPressed = false;
    }
}
void Player::MoveForward(int Direction)
{
    if(!bIsColliding)
        addPosition(jba::Vector3D(m_MovementSpeed * Direction,0,0));
}

void Player::MoveRight(int Direction)
{
    if(!bIsColliding)
        addPosition(jba::Vector3D(0,0,m_MovementSpeed * Direction));
}

void Player::CalculatePlayerY(std::shared_ptr<PlaneXY> Plane)
{

    auto playerpos = GetPosition();

    int vertZ = static_cast<int>((playerpos.x()/Plane->m_Offset) * Plane->m_Width + (playerpos.z()/Plane->m_Offset));
    if(vertZ <= 0)
        return;

    Vertex vert1 = Plane->m_Vertices[static_cast<unsigned int>(vertZ)];
    Vertex vert2 = Plane->m_Vertices[static_cast<unsigned int>((playerpos.x()/Plane->m_Offset) + 1) * Plane->m_Width + static_cast<unsigned int>((playerpos.z()/Plane->m_Offset))];
    Vertex vert3 = Plane->m_Vertices[static_cast<unsigned int>((playerpos.x()/Plane->m_Offset) + 1) * Plane->m_Width + static_cast<unsigned int>((playerpos.z()/Plane->m_Offset + 1))];

    jba::Vector2D pos1(vert1.getX(),vert1.getZ());
    jba::Vector2D pos2(vert2.getX(),vert2.getZ());
    jba::Vector2D pos3(vert3.getX(),vert3.getZ());


    jba::Vector2D playerloc(GetPosition().x(),GetPosition().z());

  //  qDebug() << playerpos << "    " << vert1.GetPosition();
    auto vec = playerloc.BarycentricCoordinates(pos1,pos2,pos3);
    if(vec.x()>=0 && vec.x()<=1 &&vec.y()>=0 && vec.y()<=1 && vec.z()>=0 && vec.z() <=1)
    {
        float y = vert1.getY() * vec.x() + vert2.getY() * vec.y() + vert3.getY() * vec.z();
        SetPosition({playerpos.x(),y+1,playerpos.z()});
    }
}
