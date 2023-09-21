#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <DirectXMath.h>
#include <atlbase.h> // Contains the declaration of CComPtr.

namespace Viewer
{
	class Renderer
	{
	public:
		bool Initialize(HWND windowHandle, unsigned int width, unsigned int height);
		void Begin();
		void End();

		inline CComPtr<ID3D11Device> GetDevice() { return m_device; }
		inline CComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_deviceContext; }

	private:
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;
		CComPtr<IDXGISwapChain> m_swapChain;


		/// <summary>
		/// A view into the back buffer texture that allows the GPU to render to it.
		/// </summary>
		CComPtr<ID3D11RenderTargetView> m_renderTargetView;

		/// <summary>
		/// A rasterizer state object describes how triangles are rendered.
		/// </summary>
		CComPtr<ID3D11RasterizerState> m_rasterizerState;

		CD3D11_VIEWPORT m_viewport;

		DirectX::XMVECTOR m_clearColor = DirectX::XMVectorSet(1.0f, 0.71f, 0.76f, 1.0f);
	};
}