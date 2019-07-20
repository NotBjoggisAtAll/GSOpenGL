#include "beziercurve.h"

using namespace jba;

BezierCurve::BezierCurve(std::shared_ptr<Shader> shader, const std::vector<Vector3D> &points, float curveSmoothness, bool drawCurve, bool drawControl) : VisualObject(shader), m_CurveSmoothness(curveSmoothness)
{
    //Default points, if none is provided
    if(points.size() == 0)
    {
        m_Points.push_back({0,1,-2});
        m_Points.push_back({-1,3,0});
        m_Points.push_back({1,3,0});
        m_Points.push_back({2,1,2});
    }
    else
    {
        m_Points = points;
    }

    m_CurveColor = {0,1,1};
    m_ControlColor = {1,0,0};

    if(drawCurve)
        DrawCurve();
    if(drawControl)
        DrawControl();
}

BezierCurve::~BezierCurve()
{
}

//Draws the curve
void BezierCurve::DrawCurve()
{
    for (GLfloat i = 0; i <= 1; i+= (1/m_CurveSmoothness))
        m_Vertices.push_back({Calculate(i), m_CurveColor});
}

//Draws the control points
void BezierCurve::DrawControl()
{
    m_Vertices.push_back({m_Points[3], m_ControlColor});
    m_Vertices.push_back({m_Points[2], m_ControlColor});
    m_Vertices.push_back({m_Points[1], m_ControlColor});
    m_Vertices.push_back({m_Points[0], m_ControlColor});
}

void BezierCurve::Init()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLuint>(m_Vertices.size()) * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void BezierCurve::Render()
{
    m_ModelMatrix = getTransformMatrix();

    m_Shader->use();
    m_Shader->setMat4("ModelMatrix", jba::Matrix4x4::transpose(*m_ModelMatrix).constData());

    glBindVertexArray(m_VAO);

    glDrawArrays(GL_LINE_STRIP,0,static_cast<GLint>(m_Vertices.size()));

    glBindVertexArray(0);
    glUseProgram(0);
}

// Used to get a position along the curve. Used for objects that wants to follow the curve
// Should run in a render/tick function
jba::Vector3D BezierCurve::GetCurvePosition()
{

    if(m_CurrentT<0)
        bIncrementT = true;
    if(m_CurrentT>1)
        bIncrementT = false;
    if (bIncrementT)
        m_CurrentT+=m_Speed/60; // 0.1f/60
    else
        m_CurrentT-=m_Speed/60;

    return Calculate(m_CurrentT);
}

float BezierCurve::GetSpeed() const { return m_Speed; }

void BezierCurve::SetSpeed(float Speed) { m_Speed = Speed; }

void BezierCurve::SetCurveColor(const Vector3D &value) { m_CurveColor = value; }

void BezierCurve::SetControlColor(const Vector3D &value) { m_ControlColor = value; }

//Cubic Bezier Curve
jba::Vector3D BezierCurve::Calculate(float t)
{
    auto CurvePoints = m_Points;

    for (unsigned int k = 1; k < CurvePoints.size(); ++k)
        for (unsigned int i = 0; i < CurvePoints.size() - k; ++i)
            CurvePoints[i] = CurvePoints[i] * (1-t) + CurvePoints[i+1] * t;

    return CurvePoints[0];
}
