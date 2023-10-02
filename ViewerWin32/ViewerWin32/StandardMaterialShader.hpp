#pragma once

#include <DirectXMath.h>
#include "shader.hpp"
#include "AmbientLight.hpp"
#include "Texture2D.hpp"

namespace Viewer
{
	class StandardMaterialShader : public Shader
	{
	public:
		StandardMaterialShader();
		void SetModelMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> modelMatrixBuffer);
		/// <summary>
		/// Sets the normal matrix for the shader
		/// </summary>
		void SetNormalMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> normalMatrixBuffer);

		void SetProjectionViewMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer>  viewMatrixBuffer);


		/// <summary>
		/// Sets the material for the shader
		/// </summary>
		void SetMaterial(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> materialBuffer);

		/// <summary>
		/// Sets the ambient light for the shader
		/// </summary>
		void SetAmbientLight(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> amibentLightBuffer);

		/// <summary>
		/// Sets the directional lights for the shader
		/// </summary>
		void SetDirectionalLights(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> directionalLightsBuffer);

		/// <summary>
		/// Sets the point lights for the shader
		/// </summary>
		void SetPointLights(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> pointLightsBuffer);

		/// <summary>
		/// Sets the diffuse texture for the shader
		/// </summary>
		void SetDiffuseTexture(CComPtr<ID3D11DeviceContext> deviceContext, Texture2D& texture);


		/// <summary>
		/// Sets the specular texture for the shader
		/// </summary>
		void SetSpecularTexture(CComPtr<ID3D11DeviceContext> deviceContext, Texture2D& texture);

		/// <summary>
		/// Sets the eye position for the shader
		/// </summary>
		void SetEyePosition(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> eyePositionBuffer);
	};
}