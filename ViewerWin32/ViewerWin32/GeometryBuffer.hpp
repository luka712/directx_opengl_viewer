#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <atlbase.h> // Contains the declaration of CComPtr.
#include <vector>

namespace Viewer
{
	class GeometryBuffer
	{
	public:
		bool Initialize(CComPtr<ID3D11Device> device, std::vector<float>& positionData, std::vector<uint16_t>& indicesData);

		void Use(CComPtr<ID3D11DeviceContext> deviceContext);

	private:

		CComPtr<ID3D11Buffer> m_vertexPositionBuffer;
		CComPtr<ID3D11Buffer> m_indexBuffer;
	};
}