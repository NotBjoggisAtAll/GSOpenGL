#ifndef SPHERE_H
#define SPHERE_H

#include "Shaders/shader.h"
#include "base/visualobject.h"
class Vertex;
typedef jba::Vector3D Vec3; // TODO IKKE Type def
class Sphere : public VisualObject {

public:
    Sphere(std::shared_ptr<Shader> shader, int n=0);
    void moveBall(float dt); //TODO Rolling ?
    void Init() override;
    void Render() override;

private:
    int m_rekursjoner;
    int m_indeks;               // brukes i rekursjon, til å bygge m_vertices
    void lagTriangel(const Vec3& v1, const Vec3& v2, const Vec3& v3);
    void subDivide(const Vec3& a, const Vec3& b, const Vec3& c, int n);
    void oktaederUnitBall();

    jba::Vector3D mRotation;

    float Radius = 1.f; //TODO Scales with the scale of the sphere
    jba::Vector3D NormalVectorPlane = jba::Vector3D(0,0,1);
    jba::Vector3D Velocity;
};


#endif // SPHERE_H
