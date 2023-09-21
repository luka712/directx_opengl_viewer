#pragma once

#include <DirectXMath.h>
#include "shader.hpp"


namespace Viewer
{
	class StandardMaterialShader : public Shader
	{
	public:
		StandardMaterialShader();
		void SetModelMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> modelMatrixBuffer);
		void SetProjectionViewMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer>  viewMatrixBuffer);
	};
}