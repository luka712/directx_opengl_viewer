#include "UnlitMaterialShader.hpp"

namespace Viewer
{
	UnlitMaterialShader::UnlitMaterialShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: Shader(device, deviceContext, "UnlitMaterialVS.hlsl", "UnlitMaterialPS.hlsl")
	{
	}

	void UnlitMaterialShader::SetCamera(CComPtr<ID3D11Buffer> cameraBuffer)
	{
		ID3D11Buffer* buffer = cameraBuffer.p;
		m_deviceContext->VSSetConstantBuffers(0, 1, &buffer);
	}

	void UnlitMaterialShader::SetTransform(CComPtr<ID3D11Buffer> transformBuffer)
	{
		ID3D11Buffer* buffer = transformBuffer.p;
		m_deviceContext->VSSetConstantBuffers(1, 1, &buffer);
	}

	void UnlitMaterialShader::SetTextureTilling(CComPtr<ID3D11Buffer> textureTillingBuffer)
	{
		ID3D11Buffer* buffer = textureTillingBuffer.p;
		m_deviceContext->VSSetConstantBuffers(2, 1, &buffer);
	}

	void UnlitMaterialShader::SetMaterial(ConstantBuffer<UnlitMaterialData>& buffer)
	{
		ID3D11Buffer* dxBuffer = buffer.GetBuffer();
		m_deviceContext->PSSetConstantBuffers(0, 1, &dxBuffer);
	}


	void UnlitMaterialShader::SetDiffuseTexture(Texture2D* texture)
	{
		ID3D11ShaderResourceView* textureView = texture->GetTextureView();
		m_deviceContext->PSSetShaderResources(0, 1, &textureView);
		ID3D11SamplerState* samplerState = texture->GetSamplerState();
		m_deviceContext->PSSetSamplers(0, 1, &samplerState);
	}
	


}