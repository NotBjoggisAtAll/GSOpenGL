#ifndef OBJECT_H
#define OBJECT_H

#include "base/visualobject.h"

class Object : public VisualObject
{
public:
    ~Object() override;
    virtual void Init() override;
    virtual void Render() override;
    Object(std::shared_ptr<Shader> Shader, QString ObjectFile, QString TextureFile="", bool MirrorHorizontally=false, bool MirrorVertically=true);
};

#endif // OBJECT_H
