#include "basescene.h"
#include "Objects/allobjects.h"
#include "Blueprints/player.h"
#include "camera.h"

BaseScene::BaseScene()
{
    m_DefaultCamera = std::make_shared<Camera>();
    m_ActiveCamera = m_DefaultCamera;
    m_Cameras.push_back(m_DefaultCamera);

    m_PhongShader = ShaderManager::GetInstance()->GetPhongShader();
    m_PlainShader = ShaderManager::GetInstance()->GetPlainShader();
    m_TextureShader = ShaderManager::GetInstance()->GetTextureShader();
    m_LightShader = ShaderManager::GetInstance()->GetLightShader();
    m_DirectionLightShader = ShaderManager::GetInstance()->GetDirectionLightShader();
    m_PointLightShader = ShaderManager::GetInstance()->GetPointLightShader();
    m_BillboardShader = ShaderManager::GetInstance()->GetBillboardShader();

    m_DefaultLight = std::make_shared<BaseLight>(m_LightShader);
    m_Axis = std::make_shared<Axis>(m_PlainShader);
    m_Axis->SetScale(100.f);
}

BaseScene::~BaseScene()
{
    m_RenderWindow = nullptr;
}

void BaseScene::Init()
{
    m_DefaultLight->Init();
    m_Axis->Init();
    //For Directional Light
    jba::Vector3D LightDirection(0.1f,-1.f,0.1f);
    m_DirectionLightShader->use();
    m_DirectionLightShader->setVec3("light.Direction", LightDirection.constData());

    //For Point Light
    m_PointLightShader->use();
    m_PointLightShader->setFloat("light.constant", 1.f);
    m_PointLightShader->setFloat("light.linear", 0.09f);
    m_PointLightShader->setFloat("light.quadratic", 0.032f);
}

void BaseScene::Render()
{
    m_ActiveCamera->Tick();

    m_DefaultLight->m_Material->m_Shader->use();
    m_DefaultLight->m_Material->m_Shader->setMat4("ViewMatrix", jba::Matrix4x4::transpose(m_ActiveCamera->GetViewMatrix()).constData());
    m_DefaultLight->Render();

    m_Axis->m_Material->m_Shader->use();
    m_Axis->m_Material->m_Shader->setMat4("ViewMatrix", jba::Matrix4x4::transpose(m_ActiveCamera->GetViewMatrix()).constData());
    m_Axis->Render();

    for(auto& Object : m_Objects)
    {
        Object->m_Material->m_Shader->use();
        Object->m_Material->m_Shader->setVec3("CameraPosition", m_ActiveCamera->GetPosition().constData());
        Object->m_Material->m_Shader->setVec3("light.Position", m_DefaultLight->GetPosition().constData());
        Object->m_Material->m_Shader->setVec3("light.Color", m_DefaultLight->GetColor().constData());
        Object->m_Material->m_Shader->setMat4("ViewMatrix", jba::Matrix4x4::transpose(m_ActiveCamera->GetViewMatrix()).constData());
        Object->Render();
    }
}

void BaseScene::KeyPressEvent(QKeyEvent *event)
{
    m_ActiveCamera->KeyPressEvent(event);
}

void BaseScene::KeyReleaseEvent(QKeyEvent *event)
{
    m_ActiveCamera->KeyReleaseEvent(event);
}

std::shared_ptr<BaseCube> BaseScene::CreateCube(std::shared_ptr<Shader> Shader)
{
    std::shared_ptr<BaseCube> cube = std::make_shared<BaseCube>(Shader);
    cube->Init();
    m_Objects.push_back(cube);
    return cube;
}

std::shared_ptr<BezierCurve> BaseScene::CreateBezierCurve(std::shared_ptr<Shader> Shader,  std::vector<jba::Vector3D> &Points, float CurveSmoothness, bool DrawCurve, bool DrawControl)
{
    std::shared_ptr<BezierCurve> bezierCurve = std::make_shared<BezierCurve>(Shader, Points, CurveSmoothness,DrawCurve, DrawControl);
    bezierCurve->Init();
    m_Objects.push_back(bezierCurve);
    return bezierCurve;
}

std::shared_ptr<Sphere> BaseScene::CreateSphere(std::shared_ptr<Shader> Shader,int Recursions)
{
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Shader, Recursions);
    sphere->Init();
    m_Objects.push_back(sphere);
    return sphere;
}

std::shared_ptr<Plane> BaseScene::CreatePlane(std::shared_ptr<Shader> Shader)
{
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(Shader);
    plane->Init();
    m_Objects.push_back(plane);
    return plane;
}

std::shared_ptr<PlaneXY> BaseScene::CreateHeightMapPlane(std::shared_ptr<Shader> Shader, const QImage &HeightMap, float Offset)
{
    std::shared_ptr<PlaneXY> plane = std::make_shared<PlaneXY>(Shader,HeightMap, Offset);
    plane->Init();
    m_Objects.push_back(plane);
    return plane;
}

std::shared_ptr<PlaneXY> BaseScene::CreatePerlinNoisePlane(std::shared_ptr<Shader> Shader, unsigned int Width, unsigned int Height, float Offset, int Octaves, int Amplitude, float Frequency)
{
    std::shared_ptr<PlaneXY> plane = std::make_shared<PlaneXY>(Shader, Width, Height, Offset, Octaves, Amplitude, Frequency);
    plane->Init();
    m_Objects.push_back(plane);
    return plane;
}

std::shared_ptr<Object> BaseScene::CreateObject(std::shared_ptr<Shader> Shader, const QString& ObjectFile, const QString& TextureFile,bool MirrorHorizontally, bool MirrorVertically)
{
    std::shared_ptr<Object> object = std::make_shared<Object>(Shader, ObjectFile, TextureFile, MirrorHorizontally, MirrorVertically);
    object->Init();
    m_Objects.push_back(object);
    return object;
}

std::shared_ptr<Billboard> BaseScene::CreateBillboard(std::shared_ptr<Camera> Camera, const QString& TextureFile, int NumberOfTiles)
{
    std::shared_ptr<Billboard> billboard = std::make_shared<Billboard>(Camera, TextureFile, NumberOfTiles);
    billboard->Init();
    m_Objects.push_back(billboard);
    return billboard;
}

std::shared_ptr<Trigger> BaseScene::CreateTrigger(bool DrawTrigger)
{
    std::shared_ptr<Trigger> trigger = std::make_shared<Trigger>(DrawTrigger);
    trigger->Init();
    m_Objects.push_back(trigger);
    return trigger;
}

std::shared_ptr<Player> BaseScene::CreatePlayer(std::shared_ptr<Sphere> PlayerObject, float MovementSpeed)
{
    std::shared_ptr<Player> player = std::make_shared<Player>(PlayerObject, MovementSpeed);
    player->Init();
    return player;
}
