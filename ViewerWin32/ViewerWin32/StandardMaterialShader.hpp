#pragma once

#include <DirectXMath.h>
#include "shader.hpp"
#include "AmbientLight.hpp"

namespace Viewer
{
	class StandardMaterialShader : public Shader
	{
	public:
		StandardMaterialShader();
		void SetModelMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> modelMatrixBuffer);
		void SetProjectionViewMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer>  viewMatrixBuffer);
		void SetAmbientLight(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> amibentLightBuffer);

		/// <summary>
		/// Sets the directional lights for the shader
		/// </summary>
		void SetDirectionalLights(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> directionalLightsBuffer);
	};
}