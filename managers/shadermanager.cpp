#include "shadermanager.h"

ShaderManager* ShaderManager::m_Instance = nullptr;

ShaderManager* ShaderManager::GetInstance()
{
    if(!m_Instance)
        m_Instance = new ShaderManager();
    return m_Instance;
}

ShaderManager::ShaderManager()
{
    m_Shaders.emplace_back(std::make_shared<Shader>("../GSOpenGL2019/Shaders/phong.vert", "../GSOpenGL2019/Shaders/phong.frag"));
    m_Shaders.emplace_back(std::make_shared<Shader>("../GSOpenGL2019/Shaders/plainvertex.vert", "../GSOpenGL2019/Shaders/plainfragment.frag"));
    m_Shaders.emplace_back(std::make_shared<Shader>("../GSOpenGL2019/Shaders/texturevertex.vert", "../GSOpenGL2019/Shaders/texturefragment.frag"));
    m_Shaders.emplace_back(std::make_shared<Shader>("../GSOpenGL2019/Shaders/plainvertex.vert", "../GSOpenGL2019/Shaders/light.frag"));
    m_Shaders.emplace_back(std::make_shared<Shader>("../GSOpenGL2019/Shaders/Lights/directional.vert", "../GSOpenGL2019/Shaders/Lights/directional.frag"));
    m_Shaders.emplace_back(std::make_shared<Shader>("../GSOpenGL2019/Shaders/Lights/point.vert", "../GSOpenGL2019/Shaders/Lights/point.frag"));
    m_Shaders.emplace_back(std::make_shared<Shader>("../GSOpenGL2019/Shaders/billboardvertex.vert", "../GSOpenGL2019/Shaders/billboardfragment.frag"));
}

ShaderManager::~ShaderManager()
{
    delete m_Instance;
    m_Instance = nullptr;
}
