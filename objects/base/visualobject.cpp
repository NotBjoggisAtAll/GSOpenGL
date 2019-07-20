#include "visualobject.h"

VisualObject::VisualObject()
{
    m_ModelMatrix = std::make_shared<jba::Matrix4x4>();
    m_Shader = nullptr;
}

VisualObject::VisualObject(std::shared_ptr<Shader> shader) : m_Shader(shader)
{
    m_ModelMatrix = std::make_shared<jba::Matrix4x4>();
}

VisualObject::~VisualObject()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
