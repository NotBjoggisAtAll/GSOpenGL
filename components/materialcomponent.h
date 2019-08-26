#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "math/vector3d.h"
#include "shaders/shader.h"
#include <QOpenGLTexture>
#include <memory>

class MaterialComponent
{
public:
    MaterialComponent(std::shared_ptr<Shader> Shader, jba::Vector3D Color = {1,0,1}, jba::Vector3D Specular = {0.5f}, float Shininess = 32)
    {
        m_Shader = Shader;
        m_Color = Color;
        m_Specular = Specular;
        m_Shininess = Shininess;
    }
    ~MaterialComponent(){}


    jba::Vector3D m_Color;
    jba::Vector3D m_Specular;
    float m_Shininess;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<QOpenGLTexture> m_Texture;
};


#endif // MATERIALCOMPONENT_H

