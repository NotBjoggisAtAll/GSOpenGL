#include "basecube.h"

BaseCube::BaseCube(std::shared_ptr<Shader> shader) : VisualObject (std::move(shader))
{

    using namespace jba;
    //                              Vertices ---------- Normals ------- TexCoords
    // Front
    m_Vertices.emplace_back(Vector3D(-1,-1, 1), Vector3D( 0, 0, 1), Vector2D(0, 1));
    m_Vertices.emplace_back(Vector3D( 1,-1, 1), Vector3D( 0, 0, 1), Vector2D(1, 1));
    m_Vertices.emplace_back(Vector3D(-1, 1, 1), Vector3D( 0, 0, 1), Vector2D(0, 0));
    m_Vertices.emplace_back(Vector3D( 1, 1, 1), Vector3D( 0, 0, 1), Vector2D(1, 0));

    // Right
    m_Vertices.emplace_back(Vector3D( 1,-1, 1), Vector3D( 1, 0, 0), Vector2D(0, 1));
    m_Vertices.emplace_back(Vector3D( 1,-1,-1), Vector3D( 1, 0, 0), Vector2D(1, 1));
    m_Vertices.emplace_back(Vector3D( 1, 1, 1), Vector3D( 1, 0, 0), Vector2D(0, 0));
    m_Vertices.emplace_back(Vector3D( 1, 1,-1), Vector3D( 1, 0, 0), Vector2D(1, 0));

    // Back
    m_Vertices.emplace_back(Vector3D( 1,-1,-1), Vector3D( 0, 0,-1), Vector2D(0, 1));
    m_Vertices.emplace_back(Vector3D(-1,-1,-1), Vector3D( 0, 0,-1), Vector2D(1, 1));
    m_Vertices.emplace_back(Vector3D( 1, 1,-1), Vector3D( 0, 0,-1), Vector2D(0, 0));
    m_Vertices.emplace_back(Vector3D(-1, 1,-1), Vector3D( 0, 0,-1), Vector2D(1, 0));

    // Left
    m_Vertices.emplace_back(Vector3D(-1,-1,-1), Vector3D(-1, 0, 0), Vector2D(0, 1));
    m_Vertices.emplace_back(Vector3D(-1,-1, 1), Vector3D(-1, 0, 0), Vector2D(1, 1));
    m_Vertices.emplace_back(Vector3D(-1, 1,-1), Vector3D(-1, 0, 0), Vector2D(0, 0));
    m_Vertices.emplace_back(Vector3D(-1, 1, 1), Vector3D(-1, 0, 0), Vector2D(1, 0));

    // Top
    m_Vertices.emplace_back(Vector3D(-1,-1,-1), Vector3D( 0,-1, 0), Vector2D(0, 1));
    m_Vertices.emplace_back(Vector3D( 1,-1,-1), Vector3D( 0,-1, 0), Vector2D(1, 1));
    m_Vertices.emplace_back(Vector3D(-1,-1, 1), Vector3D( 0,-1, 0), Vector2D(0, 0));
    m_Vertices.emplace_back(Vector3D( 1,-1, 1), Vector3D( 0,-1, 0), Vector2D(1, 0));

    // Bottom
    m_Vertices.emplace_back(Vector3D(-1, 1, 1), Vector3D( 0, 1, 0), Vector2D(0, 1));
    m_Vertices.emplace_back(Vector3D( 1, 1, 1), Vector3D( 0, 1, 0), Vector2D(1, 1));
    m_Vertices.emplace_back(Vector3D(-1, 1,-1), Vector3D( 0, 1, 0), Vector2D(0, 0));
    m_Vertices.emplace_back(Vector3D( 1, 1,-1), Vector3D( 0, 1, 0), Vector2D(1, 0));

    m_Indices = {
        0,  1,  3,  0,  3,  2,   // Front
        4,  5,  7,  4,  7,  6,   // Right
        8,  9,  11, 8,  11, 10,  // Back
        12, 13, 15, 12, 15, 14,  // Left
        16, 17, 19, 16, 19, 18,  // Top
        20, 21, 23, 20, 23, 22   // Bottom
    };
}


void BaseCube::Init()
{
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

    texture = new QOpenGLTexture(QImage("../GSOpenGL2019/Data/textures/container.png"));
}

void BaseCube::Render()
{
    if(m_IsDead)
        return;

    m_ModelMatrix = getTransformMatrix();

    m_Shader->use();
    m_Shader->setInt("TextureSampler", texture->textureId());

    m_Shader->setVec3("material.diffuse", m_Material.m_Diffuse.constData());
    m_Shader->setVec3("material.specular", m_Material.m_Specular.constData());
    m_Shader->setFloat("material.shininess", m_Material.m_Shininess);


    glActiveTexture(GL_TEXTURE0 + texture->textureId());
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    //    m_Shader->use();
    //texture->bind();


    m_Shader->setMat4("ModelMatrix", jba::Matrix4x4::transpose(*m_ModelMatrix).constData());

    glBindVertexArray(m_VAO);

    //  glDrawArrays(GL_TRIANGLES,0,static_cast<GLint>(m_Vertices.size()));

    glDrawElements(GL_TRIANGLES,static_cast<GLint>(m_Indices.size()),GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}

