#ifndef BASECUBE_H
#define BASECUBE_H
#include <QOpenGLTexture>
#include "base/visualobject.h"
class BaseCube : public VisualObject
{
public:
    BaseCube(std::shared_ptr<Shader> shader);
    virtual void Init() override;
    virtual void Render() override;

    private:

    QOpenGLTexture* texture;

};

#endif // BASECUBE_H
