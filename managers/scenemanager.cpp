#include "scenemanager.h"
#include "Scenes/allscenes.h"
SceneManager* SceneManager::m_Instance = nullptr;

SceneManager *SceneManager::GetInstance()
{
    if(!m_Instance)
        m_Instance = new SceneManager;

    return m_Instance;
}

std::shared_ptr<BaseScene> SceneManager::LoadScene(ESceneName SceneName)
{
    switch (SceneName)
    {
    case ESceneName::EMain:
        m_CurrentScene = std::make_shared<MainScene>();
        break;
    case ESceneName::EHelp:
        m_CurrentScene = std::make_shared<HelpScene>();
        break;
    case ESceneName::EHouse:
        m_CurrentScene = std::make_shared<HouseScene>();
        break;
    case ESceneName::ELight:
        m_CurrentScene = std::make_shared<LightScene>();
        break;
    case ESceneName::EBezier:
        m_CurrentScene = std::make_shared<BezierScene>();
        break;
    case ESceneName::EOblig3:
        m_CurrentScene = std::make_shared<Oblig3Scene>();
        break;
    }
    m_CurrentScene->Init();
    m_CurrentSceneName = SceneName;

    return m_CurrentScene;
}

std::shared_ptr<BaseScene> SceneManager::GetCurrentScene() const
{
    return m_CurrentScene;
}

void SceneManager::RestartScene()
{
    m_CurrentScene = LoadScene(m_CurrentSceneName);
}

SceneManager::SceneManager()
{
    LoadScene(ESceneName::EMain);
}

SceneManager::~SceneManager()
{
    delete m_Instance;
    m_Instance = nullptr;
}
