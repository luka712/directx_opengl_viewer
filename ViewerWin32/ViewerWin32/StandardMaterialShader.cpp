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

	void StandardMaterialShader::SetNormalMatrix(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> normalMatrixBuffer)
	{
		ID3D11Buffer* buffer = normalMatrixBuffer.p;
		deviceContext->VSSetConstantBuffers(2, 1, &buffer);
	}

	void StandardMaterialShader::SetMaterial(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> materialBuffer)
	{
		ID3D11Buffer* buffer = materialBuffer.p;
		deviceContext->PSSetConstantBuffers(0, 1, &buffer);
	}

	void StandardMaterialShader::SetAmbientLight(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> ambientLightBuffer)
	{
		ID3D11Buffer* buffer = ambientLightBuffer.p;
		deviceContext->PSSetConstantBuffers(1, 1, &buffer);
	}

	void StandardMaterialShader::SetDirectionalLights(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> directionalLightsBuffer)
	{
		ID3D11Buffer* buffer = directionalLightsBuffer.p;
		deviceContext->PSSetConstantBuffers(2, 1, &buffer);
	}
	void StandardMaterialShader::SetPointLights(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> pointLightsBuffer)
	{
		ID3D11Buffer* buffer = pointLightsBuffer.p;
		deviceContext->PSSetConstantBuffers(3, 1, &buffer);
	}

	void StandardMaterialShader::SetEyePosition(CComPtr<ID3D11DeviceContext> deviceContext, CComPtr<ID3D11Buffer> eyePositionBuffer)
	{
		ID3D11Buffer* buffer = eyePositionBuffer.p;
		deviceContext->PSSetConstantBuffers(4, 1, &buffer);
	}

	void StandardMaterialShader::SetDiffuseTexture(CComPtr<ID3D11DeviceContext> deviceContext, Texture2D& texture)
	{
		ID3D11ShaderResourceView* textureView = texture.GetTextureView();
		deviceContext->PSSetShaderResources(0, 1, &textureView);
		ID3D11SamplerState* samplerState = texture.GetSamplerState();
		deviceContext->PSSetSamplers(0, 1, &samplerState);
	}
	void StandardMaterialShader::SetSpecularTexture(CComPtr<ID3D11DeviceContext> deviceContext, Texture2D& texture)
	{
		ID3D11ShaderResourceView* textureView = texture.GetTextureView();
		deviceContext->PSSetShaderResources(1, 1, &textureView);
		ID3D11SamplerState* samplerState = texture.GetSamplerState();
		deviceContext->PSSetSamplers(1, 1, &samplerState);
	}


}