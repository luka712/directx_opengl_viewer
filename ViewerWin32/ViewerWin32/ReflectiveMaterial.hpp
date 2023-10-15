#pragma once

#include "MaterialData.hpp"
#include "ReflectiveMaterialShader.hpp"
#include "CubeTexture.hpp"
#include <atlbase.h>
#include "ConstantBuffer.hpp"
#include "SceneLights.hpp"
#include "Camera.hpp"
#include "Transform.hpp"

namespace Viewer
{
	class ReflectiveMaterial final
	{
	private:
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		ReflectiveMaterialShader* m_shader;

	public:
		ReflectiveMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);
		~ReflectiveMaterial();

		// Properties
		CubeTexture* EnvMapTexture;

		void Initialize();

		void Use();

		/// <summary>
		/// Updates the properties of the material. Update own properties.
		/// </summary>
		void UpdateSelfProperties();

		/// <summary>
		/// Updates the properties of the camera.
		/// </summary>
		void UpdateCameraProperties(Camera& camera);

		/// <summary>
		/// Update the properties of the transform.
		/// </summary>
		void UpdateTransformProperties(Transform& transform);
	};
}
