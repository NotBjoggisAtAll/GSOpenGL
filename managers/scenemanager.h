#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include "Scenes/Base/basescene.h"

enum class ESceneName
{
    EMain,
    EHelp,
    EHouse,
    EBezier,
    ELight,
    EOblig3
};

class SceneManager
{
public:
    static SceneManager* GetInstance();

    std::shared_ptr<BaseScene> LoadScene(ESceneName SceneName);
    std::shared_ptr<BaseScene> GetCurrentScene() const;
    void RestartScene();
private:
    SceneManager();
    ~SceneManager();

    ESceneName m_CurrentSceneName;
    std::shared_ptr<BaseScene> m_CurrentScene;
    static SceneManager* m_Instance;
};

#endif // SCENEMANAGER_H
