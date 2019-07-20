#ifndef VisualObject_H
#define VisualObject_H

#include <qopenglfunctions_4_1_core.h>
#include <memory>
#include "Shaders/shader.h"
#include "vertex.h"
#include "Math/jbamath.h"
#include "transform.h"
#include <QOpenGLTexture>

struct Material
{
    jba::Vector3D m_Diffuse{};
    jba::Vector3D m_Specular{};
    float m_Shininess = 0;

    Material(jba::Vector3D Color={}, jba::Vector3D Specular = {0.5f}, float Shininess = 32) : m_Diffuse(Color), m_Specular(Specular), m_Shininess(Shininess) {}

};


class VisualObject : public QOpenGLFunctions_4_1_Core, public Transformable
{
public:
    VisualObject();
    VisualObject(std::shared_ptr<Shader> shader);
    virtual ~VisualObject();

    virtual void Init()=0;
    virtual void Render()=0;

    void SetColor(const jba::Vector3D& Color) { m_Material.m_Diffuse = Color; }

    std::vector<Vertex> GetVertices() const { return m_Vertices; }

    std::vector<Vertex> m_Vertices; //TODO Hvorfor er du her?

    std::shared_ptr<Shader> GetShader() const { return m_Shader; }

    bool m_IsDead = false;
protected:

    std::vector<unsigned int> m_Indices;

    std::shared_ptr<jba::Matrix4x4> m_ModelMatrix;

    Material m_Material;

    std::shared_ptr<QOpenGLTexture> m_Texture;

    std::shared_ptr<Shader> m_Shader;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;

};
#endif // VisualObject_H
