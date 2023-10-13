#include "PosNormalGeometryBuffer.hpp"


Viewer::PosNormalGeometryBuffer::PosNormalGeometryBuffer(
	CComPtr<ID3D11Device> device,
	CComPtr<ID3D11DeviceContext> deviceContext)
	: m_device(device), m_deviceContext(deviceContext), m_indexCount(0)
{
}

bool Viewer::PosNormalGeometryBuffer::Initialize(
	std::vector<float>& positionData,
	std::vector<uint16_t>& indicesData,
	std::vector<float>& normalData)
{
	// Create the index buffer
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = indicesData.size() * sizeof(uint16_t);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	HRESULT hr;

	m_indexBuffer = nullptr;
	if (indicesData.size() > 0)
	{
		initData = {};
		initData.pSysMem = indicesData.data();

		m_indexCount = indicesData.size();

		hr = m_device->CreateBuffer(&ibd, &initData, &m_indexBuffer);

		if (FAILED(hr))
		{
			// Handle index buffer creation failure
			MessageBoxW(nullptr, L"Failed to create index buffer", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}

	// Create the vertex buffer
	m_vertexCount = positionData.size() / 3;

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = positionData.size() * sizeof(float);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	initData = {};
	initData.pSysMem = positionData.data();

	m_vertexPositionBuffer = nullptr;
	hr = m_device->CreateBuffer(&bd, &initData, &m_vertexPositionBuffer);

	if (FAILED(hr))
	{
		// Handle vertex buffer creation failure
		MessageBoxW(nullptr, L"Failed to create position vertex buffer", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}


	// Create the normal buffer
	m_normalBuffer = nullptr;
	if (normalData.size() > 0)
	{
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = normalData.size() * sizeof(float);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		initData = {};
		initData.pSysMem = normalData.data();

		hr = m_device->CreateBuffer(&bd, &initData, &m_normalBuffer);

		if (FAILED(hr))
		{
			// Handle vertex buffer creation failure
			MessageBoxW(nullptr, L"Failed to create normal vertex buffer", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}


	return true;
}

void Viewer::PosNormalGeometryBuffer::Use(CComPtr<ID3D11DeviceContext> deviceContext)
{
	// we assume that the vertex buffer contains only position data (3 floats per vertex)
	UINT stride = sizeof(float) * 3;
	UINT offset = 0;
	ID3D11Buffer* bufferPtr = m_vertexPositionBuffer.p; // to make the code more readable
	deviceContext->IASetVertexBuffers(0, 1, &bufferPtr, &stride, &offset);

	if (m_normalBuffer.p != nullptr)
	{
		// we assume that the vertex buffer contains only normal data (3 floats per vertex)
		stride = sizeof(float) * 3;
		bufferPtr = m_normalBuffer.p; // to make the code more readable
		deviceContext->IASetVertexBuffers(1, 1, &bufferPtr, &stride, &offset);
	}

	if (m_indexBuffer.p != nullptr)
	{
		deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	}
}

void Viewer::PosNormalGeometryBuffer::Draw()
{
	Use(m_deviceContext);

	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (m_indexCount > 0)
	{
		m_deviceContext->DrawIndexed(m_indexCount, 0, 0);
	}
	else
	{
		m_deviceContext->Draw(m_vertexCount, 0);
	}
}
