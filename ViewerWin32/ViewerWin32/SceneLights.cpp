#include "SceneLights.hpp"

namespace Viewer
{

	SceneLights::SceneLights(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_ambientLightBuffer(device, deviceContext), m_directionalLightsBuffer(device, deviceContext), m_pointLightsBuffer(device, deviceContext)
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

		// POINT LIGHTS
		m_pointLights[0].Color = { 1, 0, 0 };
		m_pointLights[0].Position = { 3, 3, 0 };

		m_pointLights[1].Color = { 0, 1, 0 };
		m_pointLights[1].Position = { 0, 3, 3 };

		m_pointLights[2].Color = { 0, 0, 1 };
		m_pointLights[2].Position = { -3, 3, 0 };

		m_pointLights[3].Color = { 1, 1, 0 };
		m_pointLights[3].Position = { 0, 3, -3 };

		m_pointLights[4].Color = { 1, 0, 1 };
		m_pointLights[4].Position = { 0, 3, 0 };
	}

	void SceneLights::Initialize()
	{
		m_ambientLightBuffer.Initialize();
		m_directionalLightsBuffer.Initialize(3);
		m_pointLightsBuffer.Initialize(5);
	}

	void SceneLights::Update()
	{
		m_ambientLightBuffer.Update(m_ambientLight);
		m_directionalLightsBuffer.Update(&m_directionalLights[0], 3);
		m_pointLightsBuffer.Update(&m_pointLights[0], 5);
	}
}
