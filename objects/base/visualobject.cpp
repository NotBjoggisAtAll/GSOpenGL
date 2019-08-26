#include "visualobject.h"
VisualObject::VisualObject()
{
    m_ModelMatrix = std::make_shared<jba::Matrix4x4>();

}

VisualObject::VisualObject(std::shared_ptr<Shader> shader)
{
    m_ModelMatrix = std::make_shared<jba::Matrix4x4>();

    m_Material = new MaterialComponent(shader);
}

VisualObject::~VisualObject()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
