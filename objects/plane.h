#ifndef PLANE_H
#define PLANE_H

#include "base/visualobject.h"

class Plane : public VisualObject
{
public:
    Plane(std::shared_ptr<Shader> shader);
    ~Plane() override;
    virtual void Init() override;
    virtual void Render() override;
};

#endif // PLANE_H
