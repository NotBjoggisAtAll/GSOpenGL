#include "trigger.h"
#include "Managers/shadermanager.h"

Trigger::Trigger(bool DrawTrigger) : m_DrawTrigger(DrawTrigger)
{
    using namespace jba;

    m_Vertices.emplace_back(Vector3D(-1,-1,-1), Vector3D(1,0,0));
    m_Vertices.emplace_back(Vector3D(1,-1,-1), Vector3D(1,0,0));
    m_Vertices.emplace_back(Vector3D(1,1,-1), Vector3D(1,0,0));
    m_Vertices.emplace_back(Vector3D(-1,1,-1), Vector3D(1,0,0));

    m_Vertices.emplace_back(Vector3D(-1,-1,1), Vector3D(1,0,0));
    m_Vertices.emplace_back(Vector3D(1,-1,1), Vector3D(1,0,0));
    m_Vertices.emplace_back(Vector3D(1,1,1), Vector3D(1,0,0));
    m_Vertices.emplace_back(Vector3D(-1,1,1), Vector3D(1,0,0));

    m_Indices = {
        0,1,
        1,2,
        2,3,
        3,0,

        0,4,
        1,5,
        2,6,
        3,7,

        4,5,
        5,6,
        6,7,
        7,4
    };
}

void Trigger::Init()
{
    m_Material = new MaterialComponent(ShaderManager::GetInstance()->GetPlainShader().get());

    initializeOpenGLFunctions();

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(m_Vertices.size()) * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(m_Indices.size()) * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

void Trigger::Render()
{
    if(m_IsDead)
        return;

    m_ModelMatrix = getTransformMatrix();

    m_Material->mShader->use();

    m_Material->mShader->setMat4("ModelMatrix", jba::Matrix4x4::transpose(*m_ModelMatrix).constData());

    glBindVertexArray(m_VAO);

    if(m_DrawTrigger)
        glDrawElements(GL_LINES,static_cast<GLint>(m_Indices.size()),GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}
