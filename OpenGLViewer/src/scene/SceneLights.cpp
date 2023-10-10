#include "scene/SceneLights.hpp"

namespace Viewer
{
    void SceneLights::Initialize()
    {
        m_ambientLight.Intensity = 0.2f;
        m_ambientLight.Color = { 1.0f, 1.0f, 1.0f };

        m_directionalLights[0].Color = { 1.0f, 1.0f, 1.0f };
        m_directionalLights[0].Direction = { 0.0f, -1.0f, 0.0f };
        m_directionalLights[0].Intensity = 0.3f;

        m_directionalLights[1].Color = { 1.0f, 1.0f, 1.0f };
        m_directionalLights[1].Intensity = 0.3f;
        m_directionalLights[1].Direction = { -1.0f, -1.0f, -1.0f };

        m_directionalLights[2].Intensity = 0.0f;

        m_pointLights[0].Color = glm::vec3(1, 0, 0);
        m_pointLights[0].Position = glm::vec3(3, 3, 0);

        m_pointLights[1].Color = glm::vec3(0, 1, 0);
        m_pointLights[1].Position = glm::vec3(0, 3, 3);

        m_pointLights[2].Color = glm::vec3(0, 0, 1);
        m_pointLights[2].Position = glm::vec3(-3, 3, 0);

        m_pointLights[3].Color = glm::vec3(1, 1, 0);
        m_pointLights[3].Position = glm::vec3(0, 3, -3);

        m_pointLights[4].Color = glm::vec3(1, 0, 1);
        m_pointLights[4].Position = glm::vec3(0, 3, 0);


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