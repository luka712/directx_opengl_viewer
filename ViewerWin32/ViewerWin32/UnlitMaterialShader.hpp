#pragma once

#include <DirectXMath.h>
#include "shader.hpp"
#include "AmbientLight.hpp"
#include "Texture2D.hpp"
#include "ConstantBuffer.hpp"
#include "MaterialData.hpp"
#include "Camera.hpp"

namespace Viewer
{
	class UnlitMaterialShader : public Shader
	{

	public:
		UnlitMaterialShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);

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
		/// Sets the texture tilling.
		/// Texture tilling is used to repeat the texture on the object. Normal value is 1,1.
		/// </summary>
		/// <param name="textureTillingBuffer"></param>
		void SetTextureTilling(CComPtr<ID3D11Buffer> textureTillingBuffer);

		/// <summary>
		/// Sets the material for the shader
		/// </summary>
		void SetMaterial(ConstantBuffer<UnlitMaterialData>& buffer);

		/// <summary>
		/// Sets the diffuse texture for the shader
		/// </summary>
		void SetDiffuseTexture(Texture2D* texture);

	};
}