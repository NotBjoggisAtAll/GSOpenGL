#include "helpscene.h"
#include <QKeyEvent>
#include "Managers/scenemanager.h"
HelpScene::HelpScene()
{

}


void HelpScene::Init()
{
    BaseScene::Init();

    GetActiveCamera()->RotationAllowed(false);
    GetActiveCamera()->MovementAllowed(false);
    GetActiveCamera()->SetPosition({0,0,3});
    m_DefaultLight->m_IsDead = true;
    m_Axis->m_IsDead = true;

    m_Keys = CreateBillboard(GetActiveCamera(), "rules.png", 1);
}

void HelpScene::Render()
{
    BaseScene::Render();
}

void HelpScene::KeyPressEvent(QKeyEvent *event)
{
    BaseScene::KeyPressEvent(event);
    if(event->key() == Qt::Key_Return)
    {
        SceneManager::GetInstance()->LoadScene(ESceneName::EMain);
    }
}

void HelpScene::KeyReleaseEvent(QKeyEvent *event)
{
    BaseScene::KeyReleaseEvent(event);
}
