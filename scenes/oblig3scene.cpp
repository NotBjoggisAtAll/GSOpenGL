#include "oblig3scene.h"
#include "blueprints/player.h"
#include "Objects/allobjects.h"
#include "Window/renderwindow.h"
#include <cmath>
#include <QKeyEvent>
#include "Managers/scenemanager.h"

Oblig3Scene::Oblig3Scene()
{

}

Oblig3Scene::~Oblig3Scene() {}

void Oblig3Scene::Init()
{
    BaseScene::Init();

    //Camera Settings
    m_ActiveCamera->SetRotation(-40,0);
    m_ActiveCamera->SetMovementSpeed(0.4f);
    m_ActiveCamera->SetPosition({-30,45,25});
    m_ActiveCamera->RotationAllowed(true);
    m_ActiveCamera->MovementAllowed(true);

    //Creates a plane and set a color
    m_Plane = CreatePerlinNoisePlane(m_DirectionLightShader,50,50,1,32,5,4);
    m_Plane->m_Material->m_Color = {0,0,0.5f};

    //Create a player and sets some default values
    m_Player = CreatePlayer(CreateSphere(m_DirectionLightShader, 3), 0.1f);
    m_Player->SetPosition({5,0,25});
    m_Player->GetPlayerObject()->m_Material->m_Color = {0.2f,1,0.8f};
    m_Player->Init();

    //Points to the BezierCurve and the Trophies
    std::vector<jba::Vector3D> TempPoints;
    TempPoints.push_back({5,3,5});
    TempPoints.push_back({45,3,5});
    TempPoints.push_back({45,3,45});
    TempPoints.push_back({5,3,45});

    for (unsigned int i = 0; i < TempPoints.size(); ++i)
    {
        m_Trophies.push_back(CreateObject(m_TextureShader, "Coin.obj", "Coin_Gold_D180322_Base_Color.png"));
        m_Trophies.at(i)->SetPosition(TempPoints.at(i));
        m_Trophies.at(i)->SetRotation({0,static_cast<float>(rand() % 360),0});
        m_TrophiesLeft++;
    }

    for (unsigned int i = 0; i < 5; ++i)
    {
        m_Walls.emplace_back(CreateCube(m_DirectionLightShader));
        m_Walls.at(i)->m_Material->m_Color = {1,0,1};
    }
    for (unsigned int i = 0; i < 2; ++i)
    {
        m_Walls.at(i)->SetScale({1,5,10.f});
    }
    m_Walls.at(2)->SetScale({1,5,25});
    for (unsigned int i = 3; i < 5; ++i)
    {
        m_Walls.at(i)->SetScale({25,5,1});
    }
    m_Walls.at(0)->SetPosition({50,2,10}); // Top Left Wall
    m_Walls.at(1)->SetPosition({50,2,40}); // Top Right Wall
    m_Walls.at(2)->SetPosition({0,2,25}); // Bot Wall
    m_Walls.at(3)->SetPosition({25,2,0}); // Left Wall
    m_Walls.at(4)->SetPosition({25,2,50}); // Right Wall

    //   m_Door = CreateObject(m_DirectionLightShader, "door.obj");
    m_Door = CreateCube(m_DirectionLightShader);
    m_Door->m_Material->m_Color = {1,0,0};
    m_Door->SetPosition({50,2,25});
    m_Door->SetScale({1,5,5});

    //Creates an enemy and set some default values
    m_Enemy = CreateObject(m_TextureShader, "PirateShip.obj", "Pirate.png");
    m_Enemy->SetScale({1});

    //Creates a Bezier Curve with some default values
    m_Curve = CreateBezierCurve(m_PlainShader,TempPoints,10,false,false);
    m_Curve->SetSpeed(1);

    m_TrophyTracker = CreateBillboard(m_ActiveCamera, "trophy-grid.png", 6);
    m_TrophyTracker->SetScale(2);
    m_TrophyTracker->SetPosition({0,10,3.5});

    m_PauseMenu = CreateBillboard(m_ActiveCamera, "pause.png", 1);
    m_PauseMenu->SetScale(3);
    m_PauseMenu->SetPosition({0,5.5f,6});

    m_GameOverMenu = CreateBillboard(GetActiveCamera(), "gameover.png", 1);
    m_GameOverMenu->SetScale(3);
    m_GameOverMenu->SetPosition({0,5.5f,6});

    m_Trigger = CreateTrigger(false);
    m_Trigger->SetPosition({52,3,25});
    m_Trigger->SetScale({1,4,10,});

}

void Oblig3Scene::Render()
{
    BaseScene::Render();

    if(b_PlayerWon)
        return;

    if(b_IsGameOver)
    {
        m_GameOverMenu->m_IsDead = false;
        return;
    }

    if(b_IsPaused)
    {
        m_PauseMenu->m_IsDead = false;
        return;
    }
    m_GameOverMenu->m_IsDead = true;
    m_PauseMenu->m_IsDead = true;
    m_Player->Tick(m_Plane);
    m_Enemy->SetPosition(m_Curve->GetCurvePosition());

    for(auto& Trophy : m_Trophies)
    {
        if(Trophy->m_IsDead == false)
        {
            Trophy->addRotation({0,1,0});
            //Check collisions for trophy pickups
            if(AABBCollision(m_Player->GetPlayerObject(), Trophy))
            {
                Trophy->m_IsDead = true;
                m_TrophiesLeft--;
                m_TrophyTracker->SetNewTile(m_TrophyTracker->GetCurrentTile() + 1);
                qDebug () << m_TrophiesLeft;
            }
        }
    }
    //Check collision for Player Vs Enemy
    if(AABBCollision(m_Player->GetPlayerObject(), m_Enemy))
    {
        b_IsGameOver = true;
    }

    if(AABBCollision(m_Player->GetPlayerObject(), m_Trigger))
    {
        if(m_TrophiesLeft == 0)
        {
            b_PlayerWon = true;
            m_TrophyTracker->SetScale(3);
            m_TrophyTracker->SetPosition({0,5.5f,6});
            m_TrophyTracker->SetNewTile(m_TrophyTracker->GetCurrentTile() + 1);
        }
    }
    for(auto& Wall : m_Walls)
    {
        if(AABBCollision(m_Player->GetPlayerObject(), Wall))
            m_Player->m_Velocity = -m_Player->m_Velocity;
    }

    // Open Door
    if(m_TrophiesLeft == 0)
    {
        if(m_Door->GetPosition().z() < 35)
            m_Door->addPosition({0,0,0.1f});
        if(m_Door->GetPosition().z() >= 35)
            m_Door->m_IsDead = true;
    }

    // Door Collision
    else if(AABBCollision(m_Player->GetPlayerObject(), m_Door))
    {
        m_Player->m_Velocity = -m_Player->m_Velocity;
    }
}

void Oblig3Scene::KeyPressEvent(QKeyEvent *event)
{
    BaseScene::KeyPressEvent(event);
    m_Player->KeyPressEvent(event);

    if(event->key() == Qt::Key_Return)
    {
        if(b_IsGameOver)
        {
            SceneManager::GetInstance()->RestartScene();
        }
    }
    if(event->key() == Qt::Key_Backspace)
    {
        if(b_IsGameOver || b_IsPaused || b_PlayerWon)
        {
            SceneManager::GetInstance()->LoadScene(ESceneName::EMain);
        }
    }
}

void Oblig3Scene::KeyReleaseEvent(QKeyEvent *event)
{
    BaseScene::KeyReleaseEvent(event);
    m_Player->KeyReleaseEvent(event);
}

bool Oblig3Scene::AABBCollision(std::shared_ptr<VisualObject> Cube1, std::shared_ptr<VisualObject> Cube2)
{
    if(!(Cube1->m_IsDead || Cube2->m_IsDead))
    {

        auto Cube1Max = Cube1->GetPosition() + Cube1->getCollisionVector();
        auto Cube1Min = Cube1->GetPosition() - Cube1->getCollisionVector();
        auto Cube2Max = Cube2->GetPosition() + Cube2->getCollisionVector();
        auto Cube2Min = Cube2->GetPosition() - Cube2->getCollisionVector();

        return (Cube1Min.x() <= Cube2Max.x() && Cube1Max.x() >= Cube2Min.x()) &&
                (Cube1Min.y() <= Cube2Max.y() && Cube1Max.y() >= Cube2Min.y()) &&
                (Cube1Min.z() <= Cube2Max.z() && Cube1Max.z() >= Cube2Min.z());
    }
    return false;
}
