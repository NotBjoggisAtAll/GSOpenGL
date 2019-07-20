#include "object.h"
#include <QString>
#include "Managers/filemanager.h"

Object::Object(std::shared_ptr<Shader> Shader, QString ObjectFile, QString TextureFile, bool MirrorHorizontally, bool MirrorVertically) : VisualObject (Shader)
{
    auto Obj = FileManager::GetInstance()->ReadFile(ObjectFile);
    m_Vertices = Obj.first;
    m_Indices = Obj.second;

    if(!TextureFile.isEmpty())
    {
        m_Texture = FileManager::GetInstance()->LoadTexture(TextureFile,MirrorHorizontally, MirrorVertically);
        // Set nearest filtering mode for texture minification
        m_Texture->setMinificationFilter(QOpenGLTexture::Nearest);
//        // Set bilinear filtering mode for texture magnification
        m_Texture->setMagnificationFilter(QOpenGLTexture::Linear);
//        // Wrap texture coordinates by repeating
//        // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
        m_Texture->setWrapMode(QOpenGLTexture::Repeat);
    }
}

Object::~Object()=default;

void Object::Init()
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
}

void Object::Render()
{
    if(m_IsDead)
        return;

    m_ModelMatrix = getTransformMatrix();

    m_Shader->use();
    m_Shader->setVec3("material.diffuse", m_Material.m_Diffuse.constData());
    m_Shader->setVec3("material.specular", m_Material.m_Specular.constData());
    m_Shader->setFloat("material.shininess", m_Material.m_Shininess);

    m_Shader->setMat4("ModelMatrix", jba::Matrix4x4::transpose(*m_ModelMatrix).constData());

    if(m_Texture)
    {
        m_Shader->setInt("TextureSampler", m_Texture->textureId());
        glActiveTexture(GL_TEXTURE0 + m_Texture->textureId());
        glBindTexture(GL_TEXTURE_2D, m_Texture->textureId());
    }

    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES,static_cast<GLint>(m_Indices.size()),GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}
