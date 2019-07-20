#ifndef IDK_H
#define IDK_H

#include "base/visualobject.h"
#include <cmath>

class PlaneXY : public VisualObject
{
public:
    //HeightMap Constructor
    PlaneXY(std::shared_ptr<Shader> Shader, const QImage &HeightMap, float Offset=5);

    //Perlin Noise Constructor
    PlaneXY(std::shared_ptr<Shader> Shader, unsigned int Width, unsigned int Height, float Offset=2, int Octaves=16, int Amplitude=5, float Frequency=8);

    virtual void Init() override;
    virtual void Render() override;

    unsigned int m_Width = 0;
    unsigned int m_Height = 0; //SET SOM PRIVATE
    float m_Offset = 0;

    bool GetSumNormals() const { return b_SumNormals; }
    void SetSumNormals(bool value) { b_SumNormals = value; Init(); }

private:

    void CalculateNormals();
    void MakeIndices();

    void NormalsSummed();

    bool b_SumNormals = false;
    std::vector<Vertex> m_SummedVertcies;

};

#endif // IDK_H
