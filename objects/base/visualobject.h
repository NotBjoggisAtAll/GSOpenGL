#ifndef VisualObject_H
#define VisualObject_H

#include <qopenglfunctions_4_1_core.h>
#include <memory>
#include "vertex.h"
#include "math/jbamath.h"
#include "transform.h"
#include "components/materialcomponent.h"

class VisualObject : public QOpenGLFunctions_4_1_Core, public Transformable
{
public:
    VisualObject();
    VisualObject(std::shared_ptr<Shader> shader);
    virtual ~VisualObject();

    virtual void Init()=0;
    virtual void Render()=0;

    MaterialComponent* m_Material;

    std::vector<Vertex> GetVertices() const { return m_Vertices; }

    std::vector<Vertex> m_Vertices; //TODO Hvorfor er du her?

    bool m_IsDead = false;
protected:

    std::vector<unsigned int> m_Indices;

    std::shared_ptr<jba::Matrix4x4> m_ModelMatrix;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;

};
#endif // VisualObject_H
