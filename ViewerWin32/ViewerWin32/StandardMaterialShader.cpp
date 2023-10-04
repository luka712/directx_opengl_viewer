#include "StandardMaterialShader.hpp"

namespace Viewer
{
	StandardMaterialShader::StandardMaterialShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: Shader(device, deviceContext, "StandardMaterialVShader.hlsl", "StandardMaterialPShader.hlsl")
	{
	}

	void StandardMaterialShader::SetCamera(CComPtr<ID3D11Buffer> cameraBuffer)
	{
		ID3D11Buffer* buffer = cameraBuffer.p;
		m_deviceContext->VSSetConstantBuffers(0, 1, &buffer);
	}

	void StandardMaterialShader::SetModelMatrix(CComPtr<ID3D11Buffer>  modelMatrixBuffer)
	{
		ID3D11Buffer* buffer = modelMatrixBuffer.p;
		m_deviceContext->VSSetConstantBuffers(1, 1, &buffer);
	}

	void StandardMaterialShader::SetNormalMatrix(CComPtr<ID3D11Buffer> normalMatrixBuffer)
	{
		ID3D11Buffer* buffer = normalMatrixBuffer.p;
		m_deviceContext->VSSetConstantBuffers(2, 1, &buffer);
	}

	void StandardMaterialShader::SetMaterial(ConstantBuffer<MaterialData>& buffer)
	{
		ID3D11Buffer* dxBuffer = buffer.GetBuffer();
		m_deviceContext->PSSetConstantBuffers(0, 1, &dxBuffer);
	}

	void StandardMaterialShader::SetAmbientLight(CComPtr<ID3D11Buffer> ambientLightBuffer)
	{
		ID3D11Buffer* buffer = ambientLightBuffer.p;
		m_deviceContext->PSSetConstantBuffers(1, 1, &buffer);
	}

	void StandardMaterialShader::SetDirectionalLights(CComPtr<ID3D11Buffer> directionalLightsBuffer)
	{
		ID3D11Buffer* buffer = directionalLightsBuffer.p;
		m_deviceContext->PSSetConstantBuffers(2, 1, &buffer);
	}
	void StandardMaterialShader::SetPointLights(CComPtr<ID3D11Buffer> pointLightsBuffer)
	{
		ID3D11Buffer* buffer = pointLightsBuffer.p;
		m_deviceContext->PSSetConstantBuffers(3, 1, &buffer);
	}


	void StandardMaterialShader::SetDiffuseTexture(Texture2D* texture)
	{
		ID3D11ShaderResourceView* textureView = texture->GetTextureView();
		m_deviceContext->PSSetShaderResources(0, 1, &textureView);
		ID3D11SamplerState* samplerState = texture->GetSamplerState();
		m_deviceContext->PSSetSamplers(0, 1, &samplerState);
	}
	void StandardMaterialShader::SetSpecularTexture(Texture2D* texture)
	{
		ID3D11ShaderResourceView* textureView = texture->GetTextureView();
		m_deviceContext->PSSetShaderResources(1, 1, &textureView);
		ID3D11SamplerState* samplerState = texture->GetSamplerState();
		m_deviceContext->PSSetSamplers(1, 1, &samplerState);
	}


}