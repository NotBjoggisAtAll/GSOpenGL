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

protected:


};

#endif // TRANSFORM_H
