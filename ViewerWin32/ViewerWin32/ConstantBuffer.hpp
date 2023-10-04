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
		ConstantBuffer(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
			: m_device(device), m_deviceContext(deviceContext)
		{
		}

		inline ID3D11Buffer* GetBuffer() { return m_buffer.p; }

		bool Initialize(int length = 1)
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

			HRESULT hr = m_device->CreateBuffer(&desc, nullptr, &m_buffer.p);

			if (FAILED(hr))
			{
				// Handle vertex buffer creation failure
				Win32ErrorUtil::DisplayLastErrorMessage();
				MessageBoxW(nullptr, L"Failed to create constant buffer", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			return true;
		}

		void Update(T Data)
		{
			m_deviceContext->UpdateSubresource(m_buffer, 0, nullptr, &Data, 0, 0);
		}

		void Update(T* Data, size_t count)
		{
			m_deviceContext->UpdateSubresource(m_buffer, 0, nullptr, Data, sizeof(T), sizeof(T) * count);
		}

	private:
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		CComPtr<ID3D11Buffer> m_buffer;

	};
}