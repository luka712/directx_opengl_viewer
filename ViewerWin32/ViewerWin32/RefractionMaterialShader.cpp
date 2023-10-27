#include "RefractionMaterialShader.hpp"

namespace Viewer
{
	RefractionMaterialShader::RefractionMaterialShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: Shader(device, deviceContext, "RefractionMaterialVS.hlsl", "RefractionMaterialPS.hlsl", "")
	{
	}

	void RefractionMaterialShader::SetCamera(CComPtr<ID3D11Buffer> cameraBuffer)
	{
		ID3D11Buffer* buffer = cameraBuffer.p;
		m_deviceContext->VSSetConstantBuffers(0, 1, &buffer);
	}

	void RefractionMaterialShader::SetTransform(CComPtr<ID3D11Buffer> transformBuffer)
	{
		ID3D11Buffer* buffer = transformBuffer.p;
		m_deviceContext->VSSetConstantBuffers(1, 1, &buffer);
	}

	void RefractionMaterialShader::SetEnvMapTexture(CubeTexture* texture)
	{
		ID3D11ShaderResourceView* textureView = texture->GetTextureView();
		m_deviceContext->PSSetShaderResources(0, 1, &textureView);
		ID3D11SamplerState* samplerState = texture->GetSamplerState();
		m_deviceContext->PSSetSamplers(0, 1, &samplerState);
	}

	void RefractionMaterialShader::SetMaterial(CComPtr<ID3D11Buffer> materialBuffer)
	{
		ID3D11Buffer* buffer = materialBuffer.p;
		m_deviceContext->PSSetConstantBuffers(0, 1, &buffer);
	}
}