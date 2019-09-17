#include "rendersystem.h"

#include "World.h"
#include "Components/meshcomponent.h"
#include "Components/transformcomponent.h"
#include "Components/materialcomponent.h"
#include "shader.h"

extern World world;

void RenderSystem::Render()
{
    initializeOpenGLFunctions();

    for(auto& entity : mEntities)
    {
        auto& mesh = world.GetComponent<Mesh>(entity);

        if(!mesh.isVisible)
            continue;

        auto& material = world.GetComponent<Material>(entity);
        auto& transform = world.GetComponent<Transform>(entity);

        glUseProgram(material.mShader->getProgram());
        glBindVertexArray(mesh.mVAO);
        material.mShader->transmitUniformData(&transform.mMatrix, &material);

        if(mesh.mIndiceCount > 0)
            glDrawElements(mesh.mDrawType, mesh.mIndiceCount, GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(mesh.mDrawType, 0, mesh.mVerticeCount);

    }
}
