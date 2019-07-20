#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <memory>
#include "Shaders/shader.h"

class ShaderManager
{
public:
    static ShaderManager* GetInstance();
    const std::vector<std::shared_ptr<Shader> > GetShaders() const { return m_Shaders; }
    const std::shared_ptr<Shader> GetPhongShader() const { return m_Shaders.at(0); }
    const std::shared_ptr<Shader> GetPlainShader() const { return m_Shaders.at(1); }
    const std::shared_ptr<Shader> GetTextureShader() const { return m_Shaders.at(2); }
    const std::shared_ptr<Shader> GetLightShader() const { return m_Shaders.at(3); }
    const std::shared_ptr<Shader> GetDirectionLightShader() const { return m_Shaders.at(4); }
    const std::shared_ptr<Shader> GetPointLightShader() const { return  m_Shaders.at(5); }
    const std::shared_ptr<Shader> GetBillboardShader() const { return  m_Shaders.at(6); }
private:
    ShaderManager();
    ~ShaderManager();

    std::vector<std::shared_ptr<Shader>> m_Shaders;
    static ShaderManager* m_Instance;
};

#endif // SHADERMANAGER_H
