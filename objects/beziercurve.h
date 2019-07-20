#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "base/visualobject.h"
#include "Math/jbamath.h"
#include "vertex.h"


class BezierCurve : public VisualObject
{
public:
    BezierCurve(std::shared_ptr<Shader> shader, const std::vector<jba::Vector3D>& points = std::vector<jba::Vector3D>(), float curveSmoothness=10, bool drawCurve = false, bool drawControl = false);
    ~BezierCurve() override;
    virtual void Init() override;
    virtual void Render() override;

    jba::Vector3D GetCurvePosition();
    float GetSpeed() const;

    void SetSpeed(float Speed=0.1f);
    void SetCurveColor(const jba::Vector3D &value);
    void SetControlColor(const jba::Vector3D &value);

private:
    void DrawCurve();
    void DrawControl();
    jba::Vector3D Calculate(float t);

    jba::Vector3D m_CurveColor;
    jba::Vector3D m_ControlColor;

    float m_CurveSmoothness;
    std::vector<jba::Vector3D> m_Points;

    float m_CurrentT = 0;
    bool bIncrementT = true;
    float m_Speed = 0.1f;

};

#endif // BEZIERCURVE_H
