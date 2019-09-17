#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

class Shader;

#include "JBA/vector3d.h"

struct Material
{
    Material(){}
    Material(Shader* Shader, jba::Vector3D Color= {1,1,1},  GLuint TextureUnit=0) : mShader(Shader), mColor(Color), mTextureUnit(TextureUnit){}
    Shader* mShader{nullptr};
    jba::Vector3D mColor{1,1,1};
    GLuint mTextureUnit{0};
};

#endif // MATERIALCOMPONENT_H
