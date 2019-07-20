#ifndef Vertex_H
#define Vertex_H

#include <ostream>
#include <istream>
#include <QDebug>
#include "math/jbamath.h"

class Vertex
{
public:
    Vertex(){}
    Vertex(float x, float y, float z) : m_Position{x,y,z}, m_Normal{}, m_UV{} {}
    Vertex(float x, float y, float z, float r, float g, float b): m_Position{x,y,z}, m_Normal{r,g,b}, m_UV{} {}
    Vertex(float x, float y, float z, float r, float g, float b, float u, float v) : m_Position{x,y,z}, m_Normal{r,g,b}, m_UV{u,v} {}
    Vertex(jba::Vector3D xyzVector) : m_Position(xyzVector), m_Normal{}, m_UV{} {}
    Vertex(jba::Vector3D xyzVector, jba::Vector3D rgbVector) : m_Position(xyzVector), m_Normal{rgbVector}, m_UV{} {}
    Vertex(jba::Vector3D xyzVector, jba::Vector3D rgbVector, jba::Vector2D uvVector) : m_Position(xyzVector), m_Normal{rgbVector}, m_UV{uvVector} {}

    void setXYZ(float xi, float yi, float zi)
    {
        m_Position.setX(xi);
        m_Position.setY(yi);
        m_Position.setZ(zi);
    }

    void setXYZ(const jba::Vector3D& xyzVector)
    {
        m_Position = xyzVector;
    }

    void setRGB(float ri, float gi, float bi)
    {
        m_Normal.setX(ri);
        m_Normal.setY(gi);
        m_Normal.setZ(bi);
    }

    void setRGB(const jba::Vector3D& rgbVector)
    {
        m_Normal = rgbVector;
    }

    void setUV(float ui, float vi)
    {
        m_UV.SetX(ui);
        m_UV.SetY(vi);
    }

    void setUV(const jba::Vector2D& uvVector)
    {
        m_UV = uvVector;
    }

    friend QDebug operator<<(QDebug d, const Vertex& v)
    {
        return d << "Position: " << v.m_Position << ", Normal: " << v.m_Normal << ", Texture: " << v.m_UV;
    }


    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream& os, const Vertex& v)
    {
        os << std::fixed;
        os << "(" << v.m_Position.x() << ", " << v.m_Position.y() << ", " << v.m_Position.z() << ") ";
        os << "(" << v.m_Normal.x() << ", " << v.m_Normal.y() << ", " << v.m_Normal.z() << ") ";
        os << "(" << v.m_UV.GetX() << ", " << v.m_UV.GetX() << ") ";
        return os;
    }

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream& is, Vertex& vertex)
    {
        // Trenger fire temporære variabler som kun skal lese inn parenteser og komma
        char dum, dum2, dum3, dum4;
        float x,y,z,r,g,b,u,v;
        is >> dum >> x >> dum2 >> y >> dum3 >> z >> dum4;
        is >> dum >> r >> dum2 >> g >> dum3 >> b >> dum4;
        is >> dum >> u >> dum2 >> v >> dum3;

        vertex.setXYZ(x,y,z);
        vertex.setRGB(r,g,b);
        vertex.setUV(u,v);

        return is;
    }

    float getX(){ return m_Position.x(); }
    void setX(float value) { m_Position.setX(value); }

    float getY(){ return m_Position.y(); }
    void setY(float value) { m_Position.setY(value); }

    float getZ(){ return m_Position.z(); }
    void setZ(float value) { m_Position.setZ(value); }

    float getR(){ return m_Normal.x(); }
    void setR(float value) { m_Normal.setX(value); }

    float getG(){ return m_Normal.y(); }
    void setG(float value) { m_Normal.setY(value); }

    float getB(){ return m_Normal.z(); }
    void setB(float value) { m_Normal.setZ(value); }

    float getU(){ return m_UV.GetX(); }
    void setU(float value) { m_UV.SetX(value); }

    float getV(){ return m_UV.GetY(); }
    void setV(float value) { m_UV.SetY(value); }

    const jba::Vector3D GetPosition() { return m_Position; }
    void SetPosition(const jba::Vector3D Vector) { m_Position = Vector; }

    const jba::Vector3D GetNormal() { return m_Normal; }
    void SetNormal(const jba::Vector3D Vector) { m_Normal = Vector; }

    const jba::Vector2D GetUV() { return m_UV; }
    void SetUV(const jba::Vector2D Vector) { m_UV = Vector; }

private:
    jba::Vector3D m_Position;
    jba::Vector3D m_Normal;
    jba::Vector2D m_UV;
};

#endif // Vertex_H
