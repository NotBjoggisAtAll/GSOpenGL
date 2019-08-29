#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "math/vector3d.h"
#include "shaders/shader.h"
#include <QOpenGLTexture>
#include <memory>

class MaterialComponent
{
public:
    MaterialComponent(Shader* Shader, jba::Vector3D Color = {1,0,1}, jba::Vector3D Specular = {0.5f}, float Shininess = 32)
    {
        mShader = Shader;
        m_Color = Color;
        m_Specular = Specular;
        m_Shininess = Shininess;
    }
    ~MaterialComponent()
    {
        delete mShader;
        mShader = nullptr;
    }


    jba::Vector3D m_Color;
    jba::Vector3D m_Specular;
    float m_Shininess;
    Shader* mShader;
    std::shared_ptr<QOpenGLTexture> m_Texture;
};


#endif // MATERIALCOMPONENT_H

