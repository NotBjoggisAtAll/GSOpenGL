#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "system.h"

class Camera;

class SoundSystem : public System
{
public:
    SoundSystem();

    void update(Camera *currCamera);

private:
};

#endif // SOUNDSYSTEM_H
