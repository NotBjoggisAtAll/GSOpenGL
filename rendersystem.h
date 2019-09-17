#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"


struct RenderSystem : public QOpenGLFunctions_4_1_Core, public System
{

    void Render();

};

#endif // RENDERSYSTEM_H
