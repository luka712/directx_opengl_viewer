#include "StandardMaterialShader.hpp"

namespace Viewer
{
StandardMaterialShader::StandardMaterialShader()
	: Shader("StandardMaterialVShader.hlsl", "StandardMaterialPShader.hlsl")
	{
	}

	void StandardMaterialShader::SetProjectionViewMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> viewMatrixBuffer)
	{
		ID3D11Buffer* buffer = viewMatrixBuffer.p;
		deviceContext->VSSetConstantBuffers(0, 1, &buffer);
	}

	void StandardMaterialShader::SetModelMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer>  modelMatrixBuffer)
	{
		ID3D11Buffer* buffer = modelMatrixBuffer.p;
		deviceContext->VSSetConstantBuffers(1, 1, &buffer);
	}

}