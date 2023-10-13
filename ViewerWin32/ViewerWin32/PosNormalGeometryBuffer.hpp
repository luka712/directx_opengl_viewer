#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <atlbase.h> // Contains the declaration of CComPtr.
#include <vector>

namespace Viewer
{
	class PosNormalGeometryBuffer
	{
	public:
		PosNormalGeometryBuffer(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);

		bool Initialize(
			std::vector<float>& positionData,
			std::vector<uint16_t>& indicesData,
			std::vector<float>& normalData);

		/// <summary>
		/// Use is also called withing <see cref="Draw"/>. so there is no need to call it before. Can be called if <see cref="Draw"/> is not used.
		/// </summary>
		/// <param name="deviceContext"></param>
		void Use(CComPtr<ID3D11DeviceContext> deviceContext);

		/// <summary>
		/// Draws the geometry. <see cref="Use"/> is called within this method.
		/// </summary>
		void Draw();

	private:
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		CComPtr<ID3D11Buffer> m_vertexPositionBuffer;
		CComPtr<ID3D11Buffer> m_indexBuffer;
		CComPtr<ID3D11Buffer> m_normalBuffer;

		size_t m_indexCount;
		size_t m_vertexCount;
	};
}