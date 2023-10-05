#include "scene/SceneLights.hpp"

namespace Viewer
{
    void SceneLights::Initialize()
    {
        m_ambientLightBuffer.Initialize();
        m_directionalLightsBuffer.Initialize(3);
        m_pointLightsBuffer.Initialize(5);
    }

    void SceneLights::Update()
    {
        m_ambientLightBuffer.Update(&m_ambientLight);
        m_directionalLightsBuffer.Update(&m_directionalLights[0], 3);
        m_pointLightsBuffer.Update(&m_pointLights[0], 5);
    }
}