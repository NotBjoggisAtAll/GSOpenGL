#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "base/visualobject.h"

class Camera;

class Billboard : public VisualObject
{
public:
    Billboard(std::shared_ptr<Camera> Camera, QString TextureFile, int NumberOfTiles);
    virtual void Init() override;
    virtual void Render() override;
    void SetNewTile(int NewTile);

    int GetCurrentTile() const { return m_CurrentTile; }
private:

    std::shared_ptr<Camera> m_Camera{};
    const jba::Vector3D m_WorldUpVector = {0, 1, 0};
    jba::Vector3D m_ForwardVector{};
    jba::Vector3D m_UpVector{};
    jba::Vector3D m_RightVector{};

    int m_NumberOfTiles{};
    int m_CurrentTile{};
    float m_TileWidth{};
    float m_MinU{};
    float m_MaxU{};
};

#endif // BILLBOARD_H
