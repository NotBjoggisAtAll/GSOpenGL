#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"

class World;


struct RenderSystem : public QOpenGLFunctions_4_1_Core, public System
{

    RenderSystem();
    void Render();

    World* world{};

};

#endif // RENDERSYSTEM_H
