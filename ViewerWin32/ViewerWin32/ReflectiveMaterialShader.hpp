#pragma once

#include <DirectXMath.h>
#include "shader.hpp"
#include "AmbientLight.hpp"
#include "CubeTexture.hpp"
#include "ConstantBuffer.hpp"
#include "MaterialData.hpp"
#include "Camera.hpp"

namespace Viewer
{
	class ReflectiveMaterialShader : public Shader
	{

	public:
		ReflectiveMaterialShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);

		/// <summary>
		/// Sets the model matrix buffers 
		/// </summary>
		void SetTransform(CComPtr<ID3D11Buffer> transformBuffer);

		/// <summary>
		/// Sets the camera buffer.
		/// It contains the projection view matrix and the eye position.
		/// </summary>
		/// <param name="cameraBuffer"></param>
		void SetCamera(CComPtr<ID3D11Buffer>  cameraBuffer);

		/// <summary>
		/// Sets the diffuse texture for the shader
		/// </summary>
		void SetEnvMapTexture(CubeTexture* texture);
	};
}