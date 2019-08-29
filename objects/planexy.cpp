#include "planexy.h"
#include "math/vector3d.h"
#include <QImage>
#include "external/PerlinNoise.hpp"


PlaneXY::PlaneXY(std::shared_ptr<Shader> Shader, const QImage& HeightMap, float Offset) : VisualObject (Shader), m_Offset(Offset)
{
    //HeightMap
    float y = 0;
    m_Height = static_cast<unsigned int>(HeightMap.height());
    m_Width = static_cast<unsigned int>(HeightMap.width());

    m_Vertices.reserve(static_cast<unsigned int>(m_Width*m_Height));
    for (float x = 0; x < m_Height; x++)
    {
        for (float z = 0; z < m_Width; z++)
        {
            y = static_cast<float>(HeightMap.pixelColor(static_cast<int>(x),static_cast<int>(z)).red());
            m_Vertices.push_back({x*Offset,y,z*Offset,0,1,0});
        }
    }
    MakeIndices();
    CalculateNormals();
    NormalsSummed();
}
PlaneXY::PlaneXY(std::shared_ptr<Shader> Shader, unsigned int Width, unsigned int Height, float Offset, int Octaves, int Amplitude, float Frequency) : VisualObject(Shader), m_Width(Width), m_Height(Height), m_Offset(Offset)
{
    //Perlin Noise
    siv::PerlinNoise PerlinNoise;
    float y = 0;
    float fx = m_Height/Frequency;
    float fz = m_Width/Frequency;

    m_Vertices.reserve(static_cast<unsigned int>(m_Width*m_Height));

    for (float x = 0; x < m_Height; x++)
    {
        for (float z = 0; z < m_Width; z++)
        {
            y = static_cast<float>(PerlinNoise.octaveNoise0_1(static_cast<double>(x/fx),static_cast<double>(z/fz),Octaves)) * Amplitude;
            m_Vertices.push_back({x*m_Offset,y,z*m_Offset,0,1,0});
        }
    }

    //Indices
    MakeIndices();

    //Calculate Normals
    CalculateNormals();
    NormalsSummed();

}
void PlaneXY::CalculateNormals()
{
    for (unsigned int x = 0; x < m_Height; x++)
    {
        for (unsigned int z = 0; z < m_Width; z++)
        {
            if(x < m_Height-1 && z < m_Width-1)
            {
                auto pos1 = m_Vertices[ x    * m_Width +  z].GetPosition();
                auto pos2 = m_Vertices[(x+1) * m_Width +  z].GetPosition();
                auto pos3 = m_Vertices[(x+1) * m_Width + (z+1)].GetPosition();

                auto normal = jba::Vector3D::cross(pos2 - pos1, pos3 - pos1);
                normal.normalize();
                m_Vertices[x*m_Width+z].setRGB(-normal);

            }
        }
    }
}

void PlaneXY::NormalsSummed()
{
    m_SummedVertcies.reserve(m_Vertices.size());
    m_SummedVertcies = m_Vertices;
    std::vector<jba::Vector3D> m_Normals;
    for (unsigned int x = 0; x < m_Height; ++x)
    {
        for (unsigned int z = 0; z < m_Width; ++z)
        {
            if(x == 0)  //Bot
            {
                if(z == 0) //Left Bot Corner
                {

                    auto normal1 = m_Vertices[(z+1) * m_Width +  x].GetNormal();
                    auto normal2 = m_Vertices[(z+1) * m_Width +  (x+1)].GetNormal();
                    auto normal3 = m_Vertices[z * m_Width +  (x+1)].GetNormal();

                    auto sum = normal1 + normal2 + normal3;
                    sum.normalize();
                    m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);

                }else if(z == m_Width-1) //Right Bot Corner
                {
                    auto normal1 = m_Vertices[(z-1) * m_Width +  x].GetNormal();
                    auto normal2 = m_Vertices[z * m_Width +  (x+1)].GetNormal();

                    auto sum = normal1 + normal2;
                    sum.normalize();
                    m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);

                }else //Bot Middle
                {
                    auto normal1 = m_Vertices[(z-1) * m_Width + x].GetNormal();
                    auto normal2 = m_Vertices[z * m_Width + (x+1)].GetNormal();
                    auto normal3 = m_Vertices[(z+1) * m_Width + (x+1)].GetNormal();
                    auto normal4 = m_Vertices[(z+1) * m_Width + x].GetNormal();

                    auto sum = normal1 + normal2 + normal3 + normal4;
                    sum.normalize();
                    m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);
                }
            }else if(z == 0)
            {
                if(x == m_Height - 1) //Left Top Corner
                {
                    auto normal1 = m_Vertices[z * m_Width + (x-1)].GetNormal();
                    auto normal2 = m_Vertices[(z+1) * m_Width + x].GetNormal();

                    auto sum = normal1 + normal2;
                    sum.normalize();
                    m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);
                }else //Left Middle
                {
                    auto normal1 = m_Vertices[z * m_Width + (x-1)].GetNormal();
                    auto normal2 = m_Vertices[(z+1) * m_Width + x].GetNormal();
                    auto normal3 = m_Vertices[(z+1) * m_Width + (x+1)].GetNormal();
                    auto normal4 = m_Vertices[z * m_Width + (x+1)].GetNormal();

                    auto sum = normal1 + normal2 + normal3 + normal4;
                    sum.normalize();
                    m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);
                }
            }else if(z == m_Width - 1)
            {
                if(x == m_Height - 1) //Right Top Corner
                {
                    auto normal1 = m_Vertices[(z-1) * m_Width + x].GetNormal();
                    auto normal2 = m_Vertices[(z-1) * m_Width + (x-1)].GetNormal();
                    auto normal3 = m_Vertices[z * m_Width + (x-1)].GetNormal();

                    auto sum = normal1 + normal2 + normal3;
                    sum.normalize();
                    m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);
                }else //Right Middle
                {
                    auto normal1 = m_Vertices[z * m_Width + (x+1)].GetNormal();
                    auto normal2 = m_Vertices[(z-1) * m_Width + x].GetNormal();
                    auto normal3 = m_Vertices[(z-1) * m_Width + (x-1)].GetNormal();
                    auto normal4 = m_Vertices[z * m_Width + (x-1)].GetNormal();

                    auto sum = normal1 + normal2 + normal3 + normal4;
                    sum.normalize();
                    m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);
                }
            }else if(x == m_Height - 1) //Top Middle
            {
                auto normal1 = m_Vertices[(z-1) * m_Width + x].GetNormal();
                auto normal2 = m_Vertices[(z-1) * m_Width + (x-1)].GetNormal();
                auto normal3 = m_Vertices[z * m_Width + (x-1)].GetNormal();
                auto normal4 = m_Vertices[(z+1) * m_Width + x].GetNormal();

                auto sum = normal1 + normal2 + normal3 + normal4;
                sum.normalize();
                m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);
            }
            else //Midten
            {
                auto normal1 = m_Vertices[z * m_Width + (x+1)].GetNormal();
                auto normal2 = m_Vertices[(z+1) * m_Width + (x+1)].GetNormal();
                auto normal3 = m_Vertices[(z+1) * m_Width + x].GetNormal();
                auto normal4 = m_Vertices[z * m_Width + (x-1)].GetNormal();
                auto normal5 = m_Vertices[(z-1) * m_Width + (x-1)].GetNormal();
                auto normal6 = m_Vertices[(z-1) * m_Width + x].GetNormal();

                auto sum = normal1 + normal2 + normal3 + normal4 + normal5 + normal6;
                sum.normalize();
                m_SummedVertcies[ x    * m_Width +  z].SetNormal(sum);
            }
        }

    }
}

void PlaneXY::MakeIndices()
{
    for (unsigned int i = 0; i < m_Width*m_Height; i++) {
        if(i == (m_Width*m_Height)-m_Height) break;
        if((i > 1) && ((i+1) % m_Width) == 0)  continue;

        m_Indices.push_back(static_cast<unsigned int>(i));
        m_Indices.push_back(static_cast<unsigned int>(i+1));
        m_Indices.push_back(static_cast<unsigned int>(i+m_Height+1));

        m_Indices.push_back(static_cast<unsigned int>(i));
        m_Indices.push_back(static_cast<unsigned int>(i+m_Height+1));
        m_Indices.push_back(static_cast<unsigned int>(i+m_Height));
    }
}

void PlaneXY::Init()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    if(b_SumNormals)
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(m_SummedVertcies.size()) * sizeof(Vertex), m_SummedVertcies.data(), GL_STATIC_DRAW);
    else
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

void PlaneXY::Render()
{
    m_ModelMatrix = getTransformMatrix();

    m_Material->mShader->use();
    m_Material->mShader->setVec3("material.diffuse", m_Material->m_Color.constData());
    m_Material->mShader->setVec3("material.specular", m_Material->m_Specular.constData());
    m_Material->mShader->setFloat("material.shininess", m_Material->m_Shininess);

    m_Material->mShader->setMat4("ModelMatrix", jba::Matrix4x4::transpose(*m_ModelMatrix).constData());

    glBindVertexArray(m_VAO);

    //glPointSize(10);
    // glDrawArrays(GL_POINTS,0,static_cast<GLint>(m_Vertices.size()));

    glDrawElements(GL_TRIANGLES,static_cast<GLsizei>(m_Indices.size()),GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}
