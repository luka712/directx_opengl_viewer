#pragma once

#include <DirectXMath.h>
#include "shader.hpp"
#include "CubeTexture.hpp"
#include "ConstantBuffer.hpp"
#include "Camera.hpp"

namespace Viewer
{
	class SkyboxShader : public Shader
	{

	public:
		SkyboxShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);

		std::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout() override;

		/// <summary>
		/// Sets the camera buffer.
		/// It contains the projection view matrix and the eye position.
		/// </summary>
		/// <param name="cameraBuffer"></param>
		void SetCamera(CComPtr<ID3D11Buffer>  cameraBuffer);

		/// <summary>
		/// Sets the diffuse texture for the shader
		/// </summary>
		void SetTexture(CubeTexture* texture);

	};
}