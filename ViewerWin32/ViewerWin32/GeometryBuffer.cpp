#include "GeometryBuffer.hpp"


bool Viewer::GeometryBuffer::Initialize(CComPtr<ID3D11Device> device,
	std::vector<float>& positionData, 
	std::vector<uint16_t>& indicesData,
	std::vector<float>& colorData)
{
	// Create the index buffer
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = indicesData.size() * sizeof(uint16_t);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = indicesData.data();

	m_indexCount = indicesData.size();

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
		MessageBoxW(nullptr, L"Failed to create position vertex buffer", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	// Create the color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = colorData.size() * sizeof(float);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	initData = {};
	initData.pSysMem = colorData.data();

	m_vertexColorBuffer = nullptr;
	hr = device->CreateBuffer(&bd, &initData, &m_vertexColorBuffer);

	if (FAILED(hr))
	{
		// Handle vertex buffer creation failure
		MessageBoxW(nullptr, L"Failed to create color vertex buffer", L"Error", MB_OK | MB_ICONERROR);
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

	// we assume that the vertex buffer contains only color data (4 floats per vertex)
	stride = sizeof(float) * 4;
	bufferPtr = m_vertexColorBuffer.p; // to make the code more readable
	deviceContext->IASetVertexBuffers(1, 1, &bufferPtr, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

void Viewer::GeometryBuffer::Draw(CComPtr<ID3D11DeviceContext> deviceContext)
{
	Use(deviceContext);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(m_indexCount, 0, 0);
}
