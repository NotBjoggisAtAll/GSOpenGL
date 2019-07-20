#include "camera.h"
#include <QCursor>
#include <QtMath>
#include <QKeyEvent>
#include "Window/renderwindow.h"

Camera::Camera(float Pitch, float Yaw, float Zoom) : m_Zoom(Zoom), m_Yaw(Yaw), m_Pitch(Pitch)
{
    m_Position = jba::Vector3D(0, 0, 3.0f);
    m_ForwardVector = jba::Vector3D(0, 0, -1.f);

    m_RightVector = m_ForwardVector ^ m_WorldUpVector;
    m_RightVector.normalize();

    m_UpVector = m_RightVector ^ m_ForwardVector;
    m_UpVector.normalize();

    m_ViewMatrix.lookAt(m_Position, m_Position + m_ForwardVector ,m_WorldUpVector);
}

Camera::~Camera()
{}

void Camera::Tick()
{
    if(b_wIsPressed)
        MoveForward(1);

    if(b_sIsPressed)
        MoveForward(-1);

    if(b_aIsPressed)
        MoveRight(-1);

    if(b_dIsPressed)
        MoveRight(1);

    if(b_qIsPressed)
        MoveUp(1);

    if(b_eIsPressed)
        MoveUp(-1);

    m_ViewMatrix.setToIdentity();
    m_ViewMatrix.lookAt(m_Position, m_Position + m_ForwardVector, m_WorldUpVector);

}

void Camera::UpdateRotation(float xOffset, float yOffset)
{

    xOffset *= m_MouseSensitivity;
    yOffset *= m_MouseSensitivity;

    if(m_RotationAllowed)
    {
        m_Yaw += xOffset;
        m_Pitch += yOffset;
    }

    if(m_Pitch > 89.0f)
        m_Pitch = 89.f;

    if(m_Pitch < -89.f)
        m_Pitch = -89.f;

    m_ForwardVector.setX(static_cast<float>(qCos(qDegreesToRadians(static_cast<double>(m_Yaw))) * qCos(qDegreesToRadians(static_cast<double>(m_Pitch)))));
    m_ForwardVector.setY(static_cast<float>(qSin(qDegreesToRadians(static_cast<double>(m_Pitch)))));
    m_ForwardVector.setZ(static_cast<float>(qSin(qDegreesToRadians(static_cast<double>(m_Yaw))) * qCos(qDegreesToRadians(static_cast<double>(m_Pitch)))));

    m_ForwardVector.normalize();

    m_RightVector = m_ForwardVector ^ m_WorldUpVector;
    m_RightVector.normalize();

    m_UpVector = m_RightVector ^ m_ForwardVector;
    m_UpVector.normalize();
}

void Camera::KeyPressEvent(QKeyEvent* event)
{
    if(m_MovementAllowed)
    {
        if(event->key() == Qt::Key_Q)
            b_qIsPressed = true;

        if(event->key() == Qt::Key_E)
            b_eIsPressed = true;

        if(event->key() == Qt::Key_W)
            b_wIsPressed = true;

        if(event->key() == Qt::Key_S)
            b_sIsPressed = true;

        if(event->key() == Qt::Key_A)
            b_aIsPressed = true;

        if(event->key() == Qt::Key_D)
            b_dIsPressed = true;
    }
}

void Camera::KeyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Q)
        b_qIsPressed = false;

    if(event->key() == Qt::Key_E)
        b_eIsPressed = false;

    if(event->key() == Qt::Key_W)
        b_wIsPressed = false;

    if(event->key() == Qt::Key_S)
        b_sIsPressed = false;

    if(event->key() == Qt::Key_A)
        b_aIsPressed = false;

    if(event->key() == Qt::Key_D)
        b_dIsPressed = false;
}

void Camera::KeyScrollEvent(QWheelEvent* event)
{
    if(m_Zoom >= 1.0f && m_Zoom <= 45.0f)
        m_Zoom -= event->delta()/64;
    if(m_Zoom <= 1.0f)
        m_Zoom = 1.0f;
    if(m_Zoom >= 45.0f)
        m_Zoom = 45.0f;
}

void Camera::MoveForward(int Direction)
{
    m_Position += m_ForwardVector * Direction * m_MovementSpeed;
}

void Camera::MoveRight(int Direction)
{
    m_Position += m_RightVector * m_MovementSpeed * Direction;
}

void Camera::MoveUp(int Direction)
{
    m_Position += m_WorldUpVector * Direction * m_MovementSpeed;
}
