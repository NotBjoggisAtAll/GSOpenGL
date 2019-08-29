#include "visualobject.h"

VisualObject::VisualObject()
{
    m_ModelMatrix = std::make_shared<jba::Matrix4x4>();
    calculateCollisionVector();

}

VisualObject::VisualObject(std::shared_ptr<Shader> shader)
{
    m_ModelMatrix = std::make_shared<jba::Matrix4x4>();
    calculateCollisionVector();
    m_Material = new MaterialComponent(shader.get());
}

VisualObject::~VisualObject()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
