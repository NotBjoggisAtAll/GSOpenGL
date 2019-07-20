#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "math/jbamath.h"
#include <memory>

struct Transform
{
    jba::Vector3D m_Position{0};
    jba::Vector3D m_Rotation{0};
    jba::Vector3D m_Scale{1};
    jba::Vector3D m_CollisionVector;

    jba::Matrix4x4 m_PositionMatrix;
    jba::Matrix4x4 m_RotationMatrix;
    jba::Matrix4x4 m_ScaleMatrix;

    Transform() {}
};

class Transformable
{
public:
    Transformable() { calculateCollisionVector(); }

    const jba::Vector3D GetPosition() const { return m_Transform.m_Position; }
    const jba::Vector3D getRotation() const { return m_Transform.m_Rotation; }
    const jba::Vector3D GetScale() const { return m_Transform.m_Scale; }
    const jba::Vector3D getCollisionVector() const { return m_Transform.m_CollisionVector; }
    const jba::Vector3D GetForwardVector() const { return m_Transform.m_RotationMatrix.getColumn(2).ToVector3D();}
    const jba::Vector3D GetRightVector() const { return m_Transform.m_RotationMatrix.getColumn(0).ToVector3D();}
    const jba::Vector3D GetUpVector() const { return m_Transform.m_RotationMatrix.getColumn(1).ToVector3D();}


    const std::shared_ptr<jba::Matrix4x4> getTransformMatrix()
    {
        m_Transform.m_PositionMatrix.setToIdentity();
        m_Transform.m_PositionMatrix.translate(m_Transform.m_Position);

        m_Transform.m_RotationMatrix.setToIdentity();
        m_Transform.m_RotationMatrix.rotate(m_Transform.m_Rotation);

        m_Transform.m_ScaleMatrix.setToIdentity();
        m_Transform.m_ScaleMatrix.scale(m_Transform.m_Scale);

        return std::make_shared<jba::Matrix4x4>(m_Transform.m_PositionMatrix * m_Transform.m_RotationMatrix * m_Transform.m_ScaleMatrix);
    }

    void SetPosition(jba::Vector3D newPosition){ m_Transform.m_Position = newPosition; }
    void SetRotation(jba::Vector3D newRotation){ m_Transform.m_Rotation = newRotation; }
    void SetScale(jba::Vector3D newScale){ m_Transform.m_Scale = newScale; calculateCollisionVector(); }

    void addPosition(jba::Vector3D addPosition){ m_Transform.m_Position += addPosition; }
    void addRotation(jba::Vector3D addRotation){ m_Transform.m_Rotation += addRotation; }
    void addScale(jba::Vector3D addScale){ m_Transform.m_Scale += addScale; calculateCollisionVector(); }

protected:

    void calculateCollisionVector()
    {
        auto lol = m_Transform.m_ScaleMatrix * jba::Vector4D(m_Transform.m_Scale);

        m_Transform.m_CollisionVector = lol.ToVector3D(); }

    Transform m_Transform;

};

#endif // TRANSFORM_H
