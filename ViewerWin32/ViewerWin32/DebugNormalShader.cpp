#include "DebugNormalShader.hpp"

namespace Viewer
{

	DebugNormalShader::DebugNormalShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: Shader(device, deviceContext, "DebugNormalVS.hlsl", "DebugNormalPS.hlsl", "DebugNormalGS.hlsl")
	{
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> DebugNormalShader::GetInputLayout()
	{
		return
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	}

	void DebugNormalShader::SetProjectionMatrix(ConstantBuffer<DirectX::XMMATRIX>& cBuffer)
	{
		ID3D11Buffer* buffer = cBuffer.GetBuffer();
		m_deviceContext->GSSetConstantBuffers(0, 1, &buffer);
	}

	void DebugNormalShader::SetViewModelMatrix(ConstantBuffer<ViewModelViewModelNormalData>& cBuffer)
	{
		ID3D11Buffer* buffer = cBuffer.GetBuffer();
		m_deviceContext->GSSetConstantBuffers(1, 1, &buffer);
	}


}
