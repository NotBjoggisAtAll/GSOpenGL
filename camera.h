#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions_4_1_Core>
#include <QPoint>
#include <memory>
#include "Math/jbamath.h"

class QKeyEvent;
class QWheelEvent;
class RenderWindow;
class Camera
{
public:
    Camera(float Pitch=0.f, float Yaw=-90.f, float Zoom=45.f);
    ~Camera();

    void Tick();
    void KeyPressEvent(QKeyEvent* event);
    void KeyReleaseEvent(QKeyEvent *event);
    void KeyScrollEvent(QWheelEvent *event);

    const jba::Matrix4x4 GetViewMatrix() const { return m_ViewMatrix; }
    const jba::Vector3D GetPosition() const { return m_Position; }

    float GetZoom() const { return m_Zoom; }
    void  SetZoom(const float& Zoom) { m_Zoom = Zoom; }

    void SetPosition(const jba::Vector3D &Position) { m_Position = Position; }

    float GetMouseSensitivity() const { return m_MouseSensitivity; }
    void SetMouseSensitivity(const float& MouseSensitivity) { m_MouseSensitivity = MouseSensitivity; }

    float GetMovementSpeed() const { return m_MovementSpeed; }
    void SetMovementSpeed(float MovementSpeed=0.05f) { m_MovementSpeed = MovementSpeed; }

    float GetPitch() const { return m_Pitch; }
    float GetYaw() const { return m_Yaw; }
    void SetRotation(float Pitch, float Yaw) { m_Pitch = Pitch; m_Yaw = Yaw; }

    void RotationAllowed(bool Value) { m_RotationAllowed = Value; }
    void MovementAllowed(bool Value) { m_MovementAllowed = Value; }

    void SetGlobalCenter(const QPoint &GlobalCenter) { m_GlobalCenter = GlobalCenter; }

    void SetRenderWindow(RenderWindow *RenderWindow) { m_RenderWindow = RenderWindow; }
    RenderWindow* GetRenderWindow() const { return m_RenderWindow; }

    void UpdateRotation(float xOffset, float yOffset);

private:

    bool m_RotationAllowed{true};
    bool m_MovementAllowed{true};

    void MoveForward(int Direction);
    void MoveRight(int Direction);
    void MoveUp(int Direction);

    RenderWindow* m_RenderWindow{};
    jba::Matrix4x4 m_ViewMatrix;

    jba::Vector3D m_Position;
    jba::Vector3D m_ForwardVector;
    jba::Vector3D m_RightVector;
    jba::Vector3D m_UpVector;
    const jba::Vector3D m_WorldUpVector = jba::Vector3D(0,1,0);

    //Mouse pos
    float m_LastX{};
    float m_LastY{};

    float m_MouseSensitivity = 0.2f;
    float m_MovementSpeed = 0.05f;

    float m_Zoom;
    float m_Yaw;
    float m_Pitch;

    QPoint m_GlobalCenter{};


    bool b_FirstMouse = true;
    bool b_wIsPressed = false;
    bool b_aIsPressed = false;
    bool b_sIsPressed = false;
    bool b_dIsPressed = false;
    bool b_qIsPressed = false;
    bool b_eIsPressed = false;

    friend QDebug operator<<(QDebug debug, const Camera& Camera) { return debug << "Position: " << Camera.GetPosition() << "Pitch: " << Camera.GetPitch() << " Yaw: " << Camera.GetYaw(); }

};

#endif // CAMERA_H
