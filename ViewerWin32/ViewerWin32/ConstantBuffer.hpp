#pragma once

#include <d3d11.h>
#include <atlbase.h> // Contains the declaration of CComPtr.

namespace Viewer
{
	template<typename T>
	class ConstantBuffer
	{
	public:

		inline ID3D11Buffer* GetBuffer() { return m_buffer.p; }

		bool Initialize(CComPtr<ID3D11Device> device)
		{
			CD3D11_BUFFER_DESC desc;
			desc.ByteWidth = sizeof(T);
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
			;
			device->CreateBuffer(&desc, nullptr, &m_buffer);
			return true;
		}

		void Update(CComPtr<ID3D11DeviceContext> deviceContext, T data)
		{
			deviceContext->UpdateSubresource(m_buffer, 0, nullptr, &data, 0, 0);
		}

	private:
		CComPtr<ID3D11Buffer> m_buffer;

	};
}