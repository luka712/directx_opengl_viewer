#include "SkyboxShader.hpp"

namespace Viewer
{

	SkyboxShader::SkyboxShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: Shader(device, deviceContext, "SkyboxVS.hlsl", "SkyboxPS.hlsl", "")
	{
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> SkyboxShader::GetInputLayout()
	{
		return
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
	}

	void SkyboxShader::SetCamera(CComPtr<ID3D11Buffer> buffer)
	{
		ID3D11Buffer* pBuffer = buffer.p;
		m_deviceContext->VSSetConstantBuffers(0, 1, &pBuffer);
	}

	void SkyboxShader::SetTexture(CubeTexture* texture)
	{
		ID3D11ShaderResourceView* textureView = texture->GetTextureView();
		m_deviceContext->PSSetShaderResources(0, 1, &textureView);
		ID3D11SamplerState* samplerState = texture->GetSamplerState();
		m_deviceContext->PSSetSamplers(0, 1, &samplerState);
	}

}
