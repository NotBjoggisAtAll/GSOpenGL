#include "billboard.h"
#include "camera.h"
#include "Managers/filemanager.h"
#include "Managers/shadermanager.h"

Billboard::Billboard(std::shared_ptr<Camera> Camera, QString TextureFile, int NumberOfTiles) : m_Camera(Camera), m_NumberOfTiles(NumberOfTiles)
{

    m_Shader = ShaderManager::GetInstance()->GetBillboardShader();
    if(!TextureFile.isEmpty())
    {
        m_Texture = FileManager::GetInstance()->LoadTexture(TextureFile);
        // Set nearest filtering mode for texture minification
        m_Texture->setMinificationFilter(QOpenGLTexture::Nearest);
        //        // Set bilinear filtering mode for texture magnification
        m_Texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //        // Wrap texture coordinates by repeating
        //        // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
        m_Texture->setWrapMode(QOpenGLTexture::Repeat);
    }
}

void Billboard::SetNewTile(int NewTile)
{
    if(NewTile > m_NumberOfTiles)
        m_CurrentTile = 5;
    else
        m_CurrentTile = NewTile;

    m_MinU = m_TileWidth * static_cast<float>(m_CurrentTile)/static_cast<float>(m_Texture->width());
    m_MaxU = m_TileWidth * static_cast<float>(m_CurrentTile + 1)/static_cast<float>(m_Texture->width());

    m_Vertices.at(0).setU(m_MinU);
    m_Vertices.at(1).setU(m_MaxU);
    m_Vertices.at(2).setU(m_MaxU);
    m_Vertices.at(3).setU(m_MinU);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(m_Vertices.size()) * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
}

void Billboard::Init()
{
    using namespace jba;

    m_TileWidth = static_cast<float>(m_Texture->width())/static_cast<float>(m_NumberOfTiles);
    m_CurrentTile = 0;
    m_MinU = m_TileWidth * static_cast<float>(m_CurrentTile)/static_cast<float>(m_Texture->width());
    m_MaxU = m_TileWidth * static_cast<float>(m_CurrentTile + 1)/static_cast<float>(m_Texture->width());



    m_Vertices.emplace_back(Vector3D(-1,-1,0), Vector3D( 0, 0, 0), Vector2D(m_MinU, 0)); // Bot Left
    m_Vertices.emplace_back(Vector3D(1,-1,0), Vector3D( 0, 0, 0), Vector2D(m_MaxU, 0));  // Bot Right
    m_Vertices.emplace_back(Vector3D(1,1,0), Vector3D( 0, 0, 0), Vector2D(m_MaxU, 1));   // Top Right
    m_Vertices.emplace_back(Vector3D(-1,1,0), Vector3D( 0, 0, 0), Vector2D(m_MinU, 1));  // Top Left

    m_Indices = {
        0,1,2,
        0,2,3
    };

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

void Billboard::Render()
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

    m_Shader->setVec3("Position", GetPosition().constData());
    m_Shader->setVec3("Scale", GetScale().constData());
    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES,static_cast<GLint>(m_Indices.size()),GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);

}
