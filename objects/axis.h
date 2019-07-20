#ifndef AXIS_H
#define AXIS_H

#include "base/visualobject.h"

class Axis : public VisualObject
{
public:
    Axis(std::shared_ptr<Shader> shader);
    virtual void Init() override;
    virtual void Render() override;
};

#endif // AXIS_H
