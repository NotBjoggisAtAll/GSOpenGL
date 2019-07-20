#ifndef BASESCENE_H
#define BASESCENE_H

#include <vector>
#include <memory>
#include "Objects/baselight.h"
#include "Objects/axis.h"
#include "Managers/shadermanager.h"
#include "camera.h"

class QImage;
class Texture;
class BezierCurve;
class Sphere;
class PlaneXY;
class Object;
class Plane;
class Player;
class Billboard;
class Trigger;

class BaseScene
{
public:
    BaseScene();
    virtual ~BaseScene();
    virtual void Init();
    virtual void Render();
    virtual void KeyPressEvent(QKeyEvent* event);
    virtual void KeyReleaseEvent(QKeyEvent* event);

    std::shared_ptr<Camera> GetActiveCamera() const { return m_ActiveCamera ;}
    std::vector<std::shared_ptr<Camera>> GetCameras() const { return m_Cameras; }
    unsigned int GetActiveCameraID() const { return m_ActiveCameraID; }
    std::shared_ptr<Axis> GetAxis() const { return m_Axis; }

    void SetActiveCameraID(unsigned int ActiveCameraID) { m_ActiveCameraID = ActiveCameraID; }

    void SetActiveCamera(std::shared_ptr<Camera> ActiveCamera) { m_ActiveCamera = ActiveCamera; }

    bool IsPaused() const {return b_IsPaused; }
    void SetPaused(bool Value) { b_IsPaused = Value; }

    std::shared_ptr<BaseCube> CreateCube(std::shared_ptr<Shader> Shader);
    std::shared_ptr<BezierCurve> CreateBezierCurve(std::shared_ptr<Shader> Shader, std::vector<jba::Vector3D> &Points, float CurveSmoothness=10, bool DrawCurve=false, bool DrawControl=false);
    std::shared_ptr<Sphere> CreateSphere(std::shared_ptr<Shader> Shader, int Recursions);
    std::shared_ptr<Plane> CreatePlane(std::shared_ptr<Shader> Shader);
    std::shared_ptr<PlaneXY> CreateHeightMapPlane(std::shared_ptr<Shader> Shader, const QImage &HeightMap, float Offset=5);
    std::shared_ptr<PlaneXY> CreatePerlinNoisePlane(std::shared_ptr<Shader> Shader, unsigned int Width, unsigned int Height, float Offset=2, int Octaves=16, int Amplitude=5, float Frequency=8);
    std::shared_ptr<Player> CreatePlayer(std::shared_ptr<Sphere> PlayerObject, float MovementSpeed=0.1f);
    std::shared_ptr<Object> CreateObject(std::shared_ptr<Shader> Shader, const QString &ObjectFile, const QString &TextureFile="", bool MirrorHorizontally=false, bool MirrorVertically=true);
    std::shared_ptr<Billboard> CreateBillboard(std::shared_ptr<Camera> Camera, const QString &TextureFile, int NumberOfTiles);
    std::shared_ptr<Trigger> CreateTrigger(bool DrawTrigger);
protected:
    std::vector<std::shared_ptr<VisualObject>> m_Objects;
    std::vector<std::shared_ptr<Camera>> m_Cameras;
    std::vector<std::shared_ptr<Texture>> m_Textures;

    std::shared_ptr<Camera> m_ActiveCamera = nullptr;
    std::shared_ptr<Camera> m_DefaultCamera = nullptr;
    unsigned int m_ActiveCameraID{0}; //TODO I Bruk?

    RenderWindow* m_RenderWindow = nullptr;

    std::shared_ptr<BaseLight> m_DefaultLight;
    std::shared_ptr<Axis> m_Axis;

    std::shared_ptr<Shader> m_PhongShader;
    std::shared_ptr<Shader> m_PlainShader;
    std::shared_ptr<Shader> m_TextureShader;
    std::shared_ptr<Shader> m_LightShader;
    std::shared_ptr<Shader> m_DirectionLightShader;
    std::shared_ptr<Shader> m_PointLightShader;
    std::shared_ptr<Shader> m_BillboardShader;

    bool b_IsPaused{false};

};

#endif // BASESCENE_H
