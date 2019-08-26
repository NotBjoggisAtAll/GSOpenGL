#include <iostream>
#include <sstream>
#include "sphere.h"
#include <QtMath>
#include "cmath"
//! \param n - the recursion level (default is 0 which makes the original Octahedron)
//!
//! The number of (duplicated) vertices are calculated based on the parameter n - the recursion level.
//! Initially we have 8 triangles, each with 3 vertices.
//! A subdivision consists of
//! - compute the midpoint of each edge in a triangel
//! - add these midpoint as vertices
//! - make three new edges by connecting new vertices
//! - preserve orientation
//! - move the three new points on the unit ball's surface by normalizing. Remember the vertex vector
//! is also a normal to the ball's surface.
//! The formula for the number of vertices is
//! m_nVertices = 3 * 8 * 4^n
//! where
//! - 3 comes from the number of vertices in a triangle,
//! - 8 comes from the original number of triangles in a regular Octahedron
//! - n is the recursion level (number of repeated subdivisions)
//!

Sphere::Sphere(std::shared_ptr<Shader> shader, int n) : VisualObject(shader), m_rekursjoner(n), m_indeks(0)
{
    m_Vertices.reserve(static_cast<unsigned int>(3 * 8 * pow(4, m_rekursjoner)));
    mRotation.setX(0);
    mRotation.setY(0);
    mRotation.setZ(0);
 //   readFile(mFilePath + "sphere.txt");
    oktaederUnitBall();
}

void Sphere::Init()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(m_Vertices.size()) * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

void Sphere::Render()
{
    m_ModelMatrix = getTransformMatrix();

    m_Material->m_Shader->use();
    m_Material->m_Shader->setVec3("material.diffuse", m_Material->m_Color.constData());
    m_Material->m_Shader->setVec3("material.specular", m_Material->m_Specular.constData());
    m_Material->m_Shader->setFloat("material.shininess", m_Material->m_Shininess);

    m_Material->m_Shader->setMat4("ModelMatrix", jba::Matrix4x4::transpose(*m_ModelMatrix).constData());

    glBindVertexArray(m_VAO);

    glDrawArrays(GL_TRIANGLES,0,static_cast<GLint>(m_Vertices.size()));

    glBindVertexArray(0);
    glUseProgram(0);
}

// Parametre inn: xyz koordinatene til et triangle v1, v2, v3 ccw
// Bevarer orienteringen av hjørnene
//!
//! \brief OctahedronBall::lagTriangel()
//! \param v1 - position on the unit ball for vertex 1
//! \param v2 - position on the unit ball for vertex 2
//! \param v3 - position on the unit ball for vertex 3
//!
//! lagTriangel() creates vertex data for a triangle's 3 vertices. This is done in the
//! final step of recursion.
//!

void Sphere::lagTriangel(const Vec3& v1, const Vec3& v2, const Vec3& v3)
{
    Vertex v;
    Vertex va;
    Vertex vb;

    v.setXYZ(v1.x(), v1.y(), v1.z());		// koordinater v.x = v1.x, v.y=v1.y, v.z=v1.z
    v.setRGB(v1.x(), v1.y(), v1.z());	// rgb
    m_Vertices.push_back(v);
    va.setXYZ(v2.x(), v2.y(), v2.z());
    va.setRGB(v2.x(), v2.y(), v2.z());
    m_Vertices.push_back(va);
    vb.setXYZ(v3.x(), v3.y(), v3.z());
    vb.setRGB(v3.x(), v3.y(), v3.z());
    m_Vertices.push_back(vb);
}

// Rekursiv subdivisjon av triangel
//!
//! \brief OctahedronBall::subDivide() recursive subdivision of a triangel
//! \param a coordinates for vertex a
//! \param b coordinates for vertex b
//! \param c coordinates for vertex c
//! \param n level of recursion
//!
//! The function tests
//! (if n>0)
//! - three new edge midpoints are computed and normalized,
//! - four new calls to subDivide() is done - one for each new triangle, preserving orientation
//! and with decreased parameter n
//! else
//! - call lagTriangel(a, b, c)
//!
void Sphere::subDivide(const Vec3& a, const Vec3& b, const Vec3& c, int n)
{
    if (n>0) {
        Vec3 v1 = a+b; v1.normalize();
        Vec3 v2 = a+c; v2.normalize();
        Vec3 v3 = c+b; v3.normalize();
        subDivide(a, v1, v2, n-1);
        subDivide(c, v2, v3, n-1);
        subDivide(b, v3, v1, n-1);
        subDivide(v3, v2, v1, n-1);
    } else {
        lagTriangel(a, b, c);
    }

}

//!
//! \brief OctahedronBall::oktaederUnitBall() creates 8 unit ball vertices and call subDivide()
//!
//! If the parameter n of the constructor OctahedronBall() is zero, the result will be the
//! original octahedron consisting of 8 triangles with duplicated vertices.
//!
void Sphere::oktaederUnitBall()
{
    Vec3 v0{0, 0, 1};
    Vec3 v1{1, 0, 0};
    Vec3 v2{0, 1, 0};
    Vec3 v3{-1, 0, 0};
    Vec3 v4{0, -1, 0};
    Vec3 v5{0, 0, -1};

    subDivide(v0, v1, v2, m_rekursjoner);
    subDivide(v0, v2, v3, m_rekursjoner);
    subDivide(v0, v3, v4, m_rekursjoner);
    subDivide(v0, v4, v1, m_rekursjoner);
    subDivide(v5, v2, v1, m_rekursjoner);
    subDivide(v5, v3, v2, m_rekursjoner);
    subDivide(v5, v4, v3, m_rekursjoner);
    subDivide(v5, v1, v4, m_rekursjoner);
}

void Sphere::moveBall(float dt)
{
    if(dt < 0){}
    mRotation = Velocity ^ NormalVectorPlane;
}
