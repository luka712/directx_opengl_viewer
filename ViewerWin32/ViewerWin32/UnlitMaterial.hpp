#pragma once

#include "MaterialData.hpp"
#include "UnlitMaterialShader.hpp"
#include "Texture2D.hpp"
#include <atlbase.h>
#include "ConstantBuffer.hpp"
#include "SceneLights.hpp"
#include "Camera.hpp"
#include "Transform.hpp"

namespace Viewer
{
	class UnlitMaterial final
	{
	private:
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		UnlitMaterialShader* m_materialShader;
		ConstantBuffer<UnlitMaterialData>* m_materialBuffer;

		ConstantBuffer<DirectX::XMFLOAT2>* m_textureTillingBuffer;

		/// <summary>
		/// To be used if no texture(Diffuse or Specular) is specified.
		/// </summary>
		Texture2D* m_emptyTexture;

	public:
		UnlitMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);
		~UnlitMaterial();

		// Properties
		Texture2D* DiffuseTexture;
		
		DirectX::XMFLOAT3 DiffuseColor;
		float Intensity;

		DirectX::XMFLOAT2 TextureTilling;

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
