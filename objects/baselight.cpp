#include "baselight.h"

BaseLight::BaseLight(std::shared_ptr<Shader> shader) : BaseCube(shader)
{
    SetScale({0.2f});
    m_Color = {1,1,1};
}

BaseLight::~BaseLight()
{

}
