#ifndef BEZIERSCENE_H
#define BEZIERSCENE_H

#include "Base/basescene.h"

class Player;
class Sphere;
class BezierCurve;

class BezierScene : public BaseScene
{
public:
    BezierScene();
    ~BezierScene() override;
    virtual void Init() override;
    virtual void Render() override;
    void KeyPressEvent(QKeyEvent *event) override;
    void KeyReleaseEvent(QKeyEvent *event) override;
private:

    std::shared_ptr<Sphere> m_Sphere;

    std::shared_ptr<BezierCurve> m_BezierCurve;
};

#endif // BEZIERSCENE_H
