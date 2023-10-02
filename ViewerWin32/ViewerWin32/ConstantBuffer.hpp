#pragma once

#include <d3d11.h>
#include <atlbase.h> // Contains the declaration of CComPtr.
#include "Win32ErrorUtil.hpp"

namespace Viewer
{
	template<typename T>
	class ConstantBuffer
	{
	public:

		inline ID3D11Buffer* GetBuffer() { return m_buffer.p; }

		bool Initialize(CComPtr<ID3D11Device> device, int length = 1)
		{
			size_t byteSize = sizeof(T) * length;

			// align to 16 bytes
			if (byteSize % 16 != 0)
			{
				byteSize += 16 - (byteSize % 16);
			}

			CD3D11_BUFFER_DESC desc;
			desc.ByteWidth = byteSize;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			HRESULT hr = device->CreateBuffer(&desc, nullptr, &m_buffer);

			if (FAILED(hr))
			{
				// Handle vertex buffer creation failure
				Win32ErrorUtil::DisplayLastErrorMessage();
				MessageBoxW(nullptr, L"Failed to create constant buffer", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			return true;
		}

		void Update(CComPtr<ID3D11DeviceContext> deviceContext, T data)
		{
			deviceContext->UpdateSubresource(m_buffer, 0, nullptr, &data, 0, 0);
		}

		void Update(CComPtr<ID3D11DeviceContext> deviceContext, T* data, size_t count)
		{
			deviceContext->UpdateSubresource(m_buffer, 0, nullptr, data, sizeof(T), sizeof(T) * count);
		}

	private:
		CComPtr<ID3D11Buffer> m_buffer;

	};
}