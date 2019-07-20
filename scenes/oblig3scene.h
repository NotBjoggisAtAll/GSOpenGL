#ifndef OBLIG3SCENE_H
#define OBLIG3SCENE_H

#include "Base/basescene.h"

class Oblig3Scene : public BaseScene
{
public:
    Oblig3Scene();
    ~Oblig3Scene() override;
    void Init() override;
    void Render() override;
    void KeyPressEvent(QKeyEvent *event) override;
    void KeyReleaseEvent(QKeyEvent *event) override;

    std::shared_ptr<Player> m_Player;
    std::shared_ptr<PlaneXY> m_Plane;
    std::shared_ptr<BezierCurve> m_Curve;
    std::shared_ptr<Object> m_Enemy;
    std::shared_ptr<BaseCube> m_Door;
    std::shared_ptr<Billboard> m_TrophyTracker;
    std::shared_ptr<Billboard> m_PauseMenu;
    std::shared_ptr<Billboard> m_GameOverMenu;
    std::shared_ptr<Trigger> m_Trigger;
    std::vector<std::shared_ptr<Object>> m_Trophies;
    std::vector<std::shared_ptr<BaseCube>> m_Walls;
private:

    int m_TrophiesLeft{};

    bool b_IsGameOver{false};
    bool b_PlayerWon{false};
    bool AABBCollision(std::shared_ptr<VisualObject> Cube1, std::shared_ptr<VisualObject> Cube2);
};

#endif // OBLIG3SCENE_H
