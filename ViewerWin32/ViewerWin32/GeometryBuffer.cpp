#include "GeometryBuffer.hpp"



bool Viewer::GeometryBuffer::Initialize(CComPtr<ID3D11Device> device, std::vector<float>& positionData, std::vector<uint16_t>& indicesData)
{
	// Create the index buffer
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = indicesData.size() * sizeof(uint16_t);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = indicesData.data();

	m_indexBuffer = nullptr;
	HRESULT hr = device->CreateBuffer(&ibd, &initData, &m_indexBuffer);

	if (FAILED(hr))
	{
		// Handle index buffer creation failure
		MessageBoxW(nullptr, L"Failed to create index buffer", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	// Create the vertex buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = positionData.size() * sizeof(float);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	initData = {};
	initData.pSysMem = positionData.data();

	m_vertexPositionBuffer = nullptr;
	 hr = device->CreateBuffer(&bd, &initData, &m_vertexPositionBuffer);

	if (FAILED(hr))
	{
		// Handle vertex buffer creation failure
		MessageBoxW(nullptr, L"Failed to create vertex buffer", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void Viewer::GeometryBuffer::Use(CComPtr<ID3D11DeviceContext> deviceContext)
{
	// we assume that the vertex buffer contains only position data (3 floats per vertex)
	UINT stride = sizeof(float) * 3;
	UINT offset = 0;
	ID3D11Buffer* bufferPtr = m_vertexPositionBuffer.p; // to make the code more readable
	deviceContext->IASetVertexBuffers(0, 1, &bufferPtr, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}
