#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <memory>
#include "Shaders/shader.h"

class ShaderManager
{
public:
    static ShaderManager* GetInstance();
    const std::vector<std::shared_ptr<Shader> > GetShaders() const { return mShaders; }
    const std::shared_ptr<Shader> GetPhongShader() const { return mShaders.at(0); }
    const std::shared_ptr<Shader> GetPlainShader() const { return mShaders.at(1); }
    const std::shared_ptr<Shader> GetTextureShader() const { return mShaders.at(2); }
    const std::shared_ptr<Shader> GetLightShader() const { return mShaders.at(3); }
    const std::shared_ptr<Shader> GetDirectionLightShader() const { return mShaders.at(4); }
    const std::shared_ptr<Shader> GetPointLightShader() const { return  mShaders.at(5); }
    const std::shared_ptr<Shader> GetBillboardShader() const { return  mShaders.at(6); }
private:
    ShaderManager();
    ~ShaderManager();

    std::vector<std::shared_ptr<Shader>> mShaders;
    static ShaderManager* m_Instance;
};

#endif // SHADERMANAGER_H
