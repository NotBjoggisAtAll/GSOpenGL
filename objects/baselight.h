#ifndef BASELIGHT_H
#define BASELIGHT_H

#include "basecube.h"

class BaseLight : public BaseCube
{
public:
    BaseLight(std::shared_ptr<Shader> shader);
    ~BaseLight() override;

    jba::Vector3D GetColor() const { return m_Color; }
private:
    jba::Vector3D m_Color{};
};

#endif // BASELIGHT_H
