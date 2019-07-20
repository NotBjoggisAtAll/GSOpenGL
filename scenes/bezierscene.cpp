#include "bezierscene.h"
#include "Window/renderwindow.h"
#include "camera.h"
#include "objects/sphere.h"
#include "Blueprints/player.h"
#include "Objects/beziercurve.h"

BezierScene::BezierScene()
{

}

BezierScene::~BezierScene() {}

void BezierScene::Init()
{
    BaseScene::Init();

    m_ActiveCamera->SetPosition({-5,0,-5});

    m_DefaultLight->SetPosition({0,5,0});

    std::vector<jba::Vector3D> points;
    points.push_back({0,1,-2});
    points.push_back({-1,3,0});
    points.push_back({2,5,0});
    points.push_back({4,6,2});

    m_BezierCurve = CreateBezierCurve(m_PlainShader, points, 16, true, true);
    m_Sphere = CreateSphere(m_PhongShader, 3);
    m_Sphere->SetScale(.2f);
    m_Sphere->SetColor({.4f,.3f,.6f});

}

void BezierScene::Render()
{
    BaseScene::Render();
    m_Sphere->SetPosition(m_BezierCurve->GetCurvePosition());

}
void BezierScene::KeyPressEvent(QKeyEvent *event)
{
    BaseScene::KeyPressEvent(event);
}

void BezierScene::KeyReleaseEvent(QKeyEvent *event)
{
    BaseScene::KeyReleaseEvent(event);
}
