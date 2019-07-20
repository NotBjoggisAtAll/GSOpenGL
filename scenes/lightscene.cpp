#include "lightscene.h"
#include "objects/basecube.h"
#include "objects/planexy.h"
#include "blueprints/player.h"
#include <QKeyEvent>
#include <QImage>

LightScene::LightScene()
{

}

LightScene::~LightScene() {}

void LightScene::Init()
{
    BaseScene::Init();
    m_DefaultCamera->SetMovementSpeed(0.5f);
    m_DefaultCamera->SetPosition({-20,50,-20});
    m_DefaultCamera->SetRotation(-25,45);

    // m_Plane = CreateHeightMapPlane(m_DirectionLightShader,QImage("../GSOpenGL2019/Data/heightmaps/bergen.png"));
   m_Plane = CreatePerlinNoisePlane(m_PointLightShader,100,100,0.5f);
    m_Plane->SetColor({0.65f,0.3f,0.6f});
    m_DefaultLight->SetPosition({25,10,25});

    auto Cube = CreateCube(m_DirectionLightShader);
    Cube->SetColor({0,1,0});
    m_Player = CreatePlayer(CreateSphere(m_DirectionLightShader, 3),0.5f);
}

void LightScene::Render()
{
    BaseScene::Render();

    m_Player->Tick(m_Plane);
}

void LightScene::KeyPressEvent(QKeyEvent *event)
{
    BaseScene::KeyPressEvent(event);
    m_Player->KeyPressEvent(event);
    if(event->key() == Qt::Key_N)
    {
        if(m_Plane->GetSumNormals())
            m_Plane->SetSumNormals(false);
        else
            m_Plane->SetSumNormals(true);
    }
}

void LightScene::KeyReleaseEvent(QKeyEvent *event)
{
    BaseScene::KeyReleaseEvent(event);
    m_Player->KeyReleaseEvent(event);
}
