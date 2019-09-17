#ifndef WORLD_H
#define WORLD_H

#include "Managers/componentManager.h"
#include "entitymanager.h"
#include "systemManager.h"
#include <memory>

class World
{
public:

    static World* getWorld()
    {
        if(instance == nullptr)
            instance = new World();

        return instance;
    }

    void Init()
    {
        // Create pointers to each manager
        mComponentManager = std::make_unique<ComponentManager>();
        mEntityManager = std::make_unique<EntityManager>();
        mSystemManager = std::make_unique<SystemManager>();
    }


    // Entity methods
    Entity createEntity()
    {
        return mEntityManager->createEntity();
    }

    void destroyEntity(Entity entity)
    {
        mEntityManager->destroyEntity(entity);

        mComponentManager->entityDestroyed(entity);

        mSystemManager->entityDestroyed(entity);
    }


    // Component methods
    template<typename T>
    void RegisterComponent()
    {
        mComponentManager->registerComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        mComponentManager->addComponent<T>(entity, component);

        auto signature = mEntityManager->getSignature(entity);
        signature.set(mComponentManager->getComponentType<T>(), true);
        mEntityManager->setSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity)
    {
        mComponentManager->removeComponent<T>(entity);

        auto signature = mEntityManager->getSignature(entity);
        signature.set(mComponentManager->getComponentType<T>(), false);
        mEntityManager->setSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity entity)
    {
        return mComponentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType()
    {
        return mComponentManager->getComponentType<T>();
    }


    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return mSystemManager->registerSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature)
    {
        mSystemManager->setSignature<T>(signature);
    }

private:

    static World* instance;
    World(){Init();}

    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<SystemManager> mSystemManager;

};


#endif // WORLD_H
