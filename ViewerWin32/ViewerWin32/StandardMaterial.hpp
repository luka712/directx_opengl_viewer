#pragma once

#include "MaterialData.hpp"
#include "StandardMaterialShader.hpp"
#include "Texture2D.hpp"
#include <atlbase.h>
#include "ConstantBuffer.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

namespace Viewer
{
	class StandardMaterial final
	{
	private:
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		StandardMaterialShader* m_materialShader;
		ConstantBuffer<MaterialData> *m_materialBuffer;

		/// <summary>
		/// To be used if no texture(Diffuse or Specular) is specified.
		/// </summary>
		Texture2D* m_emptyTexture;

	public:
		StandardMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);
		~StandardMaterial();

		// Properties
		Texture2D* DiffuseTexture;
		Texture2D* SpecularTexture;
		float DiffuseCoefficient;
		float SpecularCoefficient;
		float Shininess;

		void Initialize();

		void Use();

		/// <summary>
		/// Updates the properties of the material. Update own properties.
		/// </summary>
		void UpdateSelfProperties();

		/// <summary>
		/// Updates the properties of the camera.
		/// </summary>
		void UpdateCameraProperties(ConstantBuffer<DirectX::XMMATRIX> projectionViewMatrixBuffer, ConstantBuffer<DirectX::XMVECTOR> eyePositionBuffer);

		/// <summary>
		/// Update the properties of the transform.
		/// </summary>
		void UpdateTransformProperties(ConstantBuffer<DirectX::XMMATRIX> worldMatrixBuffer, ConstantBuffer<DirectX::XMMATRIX> normalMatrixBuffer);

		/// <summary>
		/// Update the properties of the lights.
		/// </summary>
		void UpdateLightsProperties(ConstantBuffer<AmbientLight> ambientLightBuffer, ConstantBuffer<DirectionalLight> directionalLightBuffer,
			ConstantBuffer<PointLight> pointLightBuffer);
	};
}
