#pragma once

#include <DirectXMath.h>
#include "ConstantBuffer.hpp"
#include <atlbase.h> // Contains the declaration of CComPtr.

namespace Viewer
{
	class Transform
	{
	public:
		Transform(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);

		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Rotation;
		DirectX::XMFLOAT3 Scale;

		/// <summary>
		/// Set on each update.
		/// </summary>
		DirectX::XMMATRIX ModelMatrix;

		/// <summary>
		/// Initialize the transform object.
		/// </summary>
		void Initialize();

		/// <summary>
		/// Updates the transform object.
		/// </summary>
		void Update();

		ConstantBuffer<DirectX::XMMATRIX>& GetBuffer() { return m_buffer; }


	private:
		ConstantBuffer<DirectX::XMMATRIX> m_buffer;

	};
};
