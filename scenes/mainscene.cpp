#include "mainscene.h"
#include <QKeyEvent>
#include "Managers/scenemanager.h"
#include "Objects/billboard.h"
MainScene::MainScene()
{
}

MainScene::~MainScene() {}

void MainScene::Init()
{
    BaseScene::Init();

    GetActiveCamera()->RotationAllowed(false);
    GetActiveCamera()->MovementAllowed(false);
    GetActiveCamera()->SetPosition({0,0,5});
    m_DefaultLight->m_IsDead = true;
    m_Axis->m_IsDead = true;

    m_Play = CreateBillboard(GetActiveCamera(), "playbutton.png", 2);
    m_Play->SetPosition({0,0.5f,0});
    m_Help = CreateBillboard(GetActiveCamera(), "helpbutton.png", 2);
    m_Help->SetNewTile(1);
    m_Help->SetPosition({0,-0.5f,0});

    m_ActiveBillboard = m_Play;

}


void MainScene::Render()
{
    BaseScene::Render();
}
void MainScene::KeyPressEvent(QKeyEvent *event)
{
    BaseScene::KeyPressEvent(event);
    if(event->key() == Qt::Key_Up)
    {
        m_Play->SetNewTile(0);
        m_Help->SetNewTile(1);
        m_ActiveBillboard = m_Play;
    }
    if(event->key() == Qt::Key_Down)
    {
        m_Play->SetNewTile(1);
        m_Help->SetNewTile(0);
        m_ActiveBillboard = m_Help;

    }
    if(event->key() == Qt::Key_Return)
    {
        if(m_ActiveBillboard == m_Play)
        {
            SceneManager::GetInstance()->LoadScene(ESceneName::EOblig3);
        }
        else if(m_ActiveBillboard == m_Help)
        {
            SceneManager::GetInstance()->LoadScene(ESceneName::EHelp);
        }
    }
}

void MainScene::KeyReleaseEvent(QKeyEvent *event)
{
    BaseScene::KeyReleaseEvent(event);
}
