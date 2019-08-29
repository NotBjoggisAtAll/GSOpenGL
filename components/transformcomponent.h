#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "math/vector3d.h"
#include "math/matrix4x4.h"

struct TransformComponent
{
    TransformComponent(jba::Vector3D position = {0}, jba::Vector3D rotation = {0}, jba::Vector3D scale = {1})
        : Position(position), Rotation(rotation), Scale(scale) {}
     ~TransformComponent(){}

    jba::Vector3D Position;
    jba::Vector3D Rotation;
    jba::Vector3D Scale;

    jba::Vector3D CollisionVector;

    jba::Matrix4x4 PositionMatrix;
    jba::Matrix4x4 RotationMatrix;
    jba::Matrix4x4 ScaleMatrix;

};

#endif // TRANSFORMCOMPONENT_H
