#pragma once

#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "ConstantBuffer.hpp"
#include <exception>
#include <atlbase.h> // Contains the declaration of CComPtr.


namespace Viewer
{
	class SceneLights
	{
	public:
		SceneLights(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);

		/// <summary>
		/// Initialize the lights.
		/// </summary>
		void Initialize();

		/// <summary>
		/// Update the lights.
		/// </summary>
		void Update();

		/// <summary>
		/// Gets the ambient light.
		/// </summary>
		/// <returns></returns>
		inline AmbientLight& GetAmbientLight() { return m_ambientLight; }

		/// <summary>
		/// Gets the ambient light buffer.
		/// </summary>
		/// <returns></returns>
		inline ConstantBuffer<AmbientLight>& GetAmbientLightBuffer() { return m_ambientLightBuffer; }

		/// <summary>
		/// Gets the directional lights.
		/// </summary>
		inline DirectionalLight& GetDirectionalLights(int index)
		{
			if (index > 2 || index < 0)
			{
				throw std::exception("Index out of range");
			}

			return m_directionalLights[index]; 
		}

		/// <summary>
		/// Gets the directional lights buffer.
		/// </summary>
		/// <returns></returns>
		inline ConstantBuffer<DirectionalLight>& GetDirectionalLightsBuffer() { return m_directionalLightsBuffer; }

		/// <summary>
		/// Gets the point lights.
		/// </summary>
		inline PointLight& GetPointLights(int index)
		{
			if (index > 4 || index < 0)
			{
				throw std::exception("Index out of range");
			}

			return m_pointLights[index];
		}

		/// <summary>
		/// Gets the point lights buffer.
		/// </summary>
		inline ConstantBuffer<PointLight>& GetPointLightsBuffer() { return m_pointLightsBuffer; }

	private:

		AmbientLight m_ambientLight;

		/// <summary>
		/// Ambient light buffer.
		/// </summary>
		ConstantBuffer<AmbientLight> m_ambientLightBuffer;

		DirectionalLight m_directionalLights[3];

		/// <summary>
		/// Directional lights buffer.
		/// </summary>
		ConstantBuffer<DirectionalLight> m_directionalLightsBuffer;

		PointLight m_pointLights[5];

		/// <summary>
		/// Point lights buffer.
		/// </summary>
		ConstantBuffer<PointLight> m_pointLightsBuffer;

	};
}