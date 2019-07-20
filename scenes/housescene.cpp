#include "housescene.h"
#include "camera.h"
#include "Objects/allobjects.h"
#include "Blueprints/player.h"
#include "QKeyEvent"
#include "Math/jbamath.h"

HouseScene::HouseScene()
= default;
HouseScene::~HouseScene()
= default;

void HouseScene::Init()
{
    BaseScene::Init();
    m_Cameras.emplace_back(std::make_shared<Camera>(0,0));
    m_Cameras.at(1)->SetPosition(jba::Vector3D(5.5f,1,3.5f));
    m_DefaultCamera->SetPosition(jba::Vector3D(-11,5,10));
    m_ActiveCamera->SetMovementSpeed(2.5f);

    auto Bill = CreateBillboard(m_ActiveCamera, "trophy-grid.png", 5);
    Bill->SetPosition({5,0,0});
    m_Cube = CreateCube(m_TextureShader);

    m_Player = CreatePlayer(CreateSphere(m_PhongShader,3));

    m_Cube->SetPosition(jba::Vector3D(12,0.5,0));
    m_Cube->SetColor({1,0,1});

    m_Car = CreateObject(m_TextureShader, "coin.obj", "coinA.png");
    m_Car->SetPosition({5,0,0});
    // m_Car->SetColor({1,0.8f,0.2f});

}

void HouseScene::Render()
{
    BaseScene::Render();
    m_Player->Tick();
}

void HouseScene::KeyPressEvent(QKeyEvent *event)
{
    m_ActiveCamera->KeyPressEvent(event);
    m_Player->KeyPressEvent(event);
}

void HouseScene::KeyReleaseEvent(QKeyEvent *event)
{
    m_ActiveCamera->KeyReleaseEvent(event);
    m_Player->KeyReleaseEvent(event);
}
