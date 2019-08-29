#ifndef VisualObject_H
#define VisualObject_H

#include <qopenglfunctions_4_1_core.h>
#include <memory>
#include "vertex.h"
#include "math/jbamath.h"
#include "components/transformcomponent.h"
#include "components/materialcomponent.h"

class VisualObject : public QOpenGLFunctions_4_1_Core
{
public:
    VisualObject();
    VisualObject(std::shared_ptr<Shader> shader);
    virtual ~VisualObject();

    virtual void Init()=0;
    virtual void Render()=0;

    MaterialComponent* m_Material;
    TransformComponent m_Transform;

    std::vector<Vertex> GetVertices() const { return m_Vertices; }

    std::vector<Vertex> m_Vertices; //TODO Hvorfor er du her?

    bool m_IsDead = false;

    const jba::Vector3D GetPosition() const { return m_Transform.Position; }
    const jba::Vector3D getRotation() const { return m_Transform.Rotation; }
    const jba::Vector3D GetScale() const { return m_Transform.Scale; }
    const jba::Vector3D getCollisionVector() const { return m_Transform.CollisionVector; }
    const jba::Vector3D GetForwardVector() const { return m_Transform.RotationMatrix.getColumn(2).ToVector3D();}
    const jba::Vector3D GetRightVector() const { return m_Transform.RotationMatrix.getColumn(0).ToVector3D();}
    const jba::Vector3D GetUpVector() const { return m_Transform.RotationMatrix.getColumn(1).ToVector3D();}


    const std::shared_ptr<jba::Matrix4x4> getTransformMatrix()
    {
        m_Transform.PositionMatrix.setToIdentity();
        m_Transform.PositionMatrix.translate(m_Transform.Position);

        m_Transform.RotationMatrix.setToIdentity();
        m_Transform.RotationMatrix.rotate(m_Transform.Rotation);

        m_Transform.ScaleMatrix.setToIdentity();
        m_Transform.ScaleMatrix.scale(m_Transform.Scale);

        return std::make_shared<jba::Matrix4x4>(m_Transform.PositionMatrix * m_Transform.RotationMatrix * m_Transform.ScaleMatrix);
    }

    void SetPosition(jba::Vector3D newPosition){ m_Transform.Position = newPosition; }
    void SetRotation(jba::Vector3D newRotation){ m_Transform.Rotation = newRotation; }
    void SetScale(jba::Vector3D newScale){ m_Transform.Scale = newScale; calculateCollisionVector(); }

    void addPosition(jba::Vector3D addPosition){ m_Transform.Position += addPosition; }
    void addRotation(jba::Vector3D addRotation){ m_Transform.Rotation += addRotation; }
    void addScale(jba::Vector3D addScale){ m_Transform.Scale += addScale; calculateCollisionVector(); }

protected:

    void calculateCollisionVector()
    {
        auto lol = m_Transform.ScaleMatrix * jba::Vector4D(m_Transform.Scale);

        m_Transform.CollisionVector = lol.ToVector3D(); }



    std::vector<unsigned int> m_Indices;

    std::shared_ptr<jba::Matrix4x4> m_ModelMatrix;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;

};
#endif // VisualObject_H
