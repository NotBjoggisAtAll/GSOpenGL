#include "axis.h"

Axis::Axis(std::shared_ptr<Shader> shader) : VisualObject(shader)
{
    using namespace jba;
    m_Vertices.push_back({Vector3D(0, 0, 0),Vector3D(1, 0, 0)});
    m_Vertices.push_back({Vector3D(1, 0, 0),Vector3D(1, 0, 0)});
    m_Vertices.push_back({Vector3D(0, 0, 0),Vector3D(0, 1, 0)});
    m_Vertices.push_back({Vector3D(0, 1, 0),Vector3D(0, 1, 0)});
    m_Vertices.push_back({Vector3D(0, 0, 0),Vector3D(0, 0, 1)});
    m_Vertices.push_back({Vector3D(0, 0, 1),Vector3D(0, 0, 1)});
}

void Axis::Init()
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

void Axis::Render()
{
    if(m_IsDead)
        return;

    m_ModelMatrix = getTransformMatrix();

    m_Material->m_Shader->use();
    m_Material->m_Shader->setMat4("ModelMatrix", jba::Matrix4x4::transpose(*m_ModelMatrix).constData());

    glBindVertexArray(m_VAO);

    glDrawArrays(GL_LINES,0,static_cast<GLint>(m_Vertices.size()));

    glBindVertexArray(0);
    glUseProgram(0);
}

