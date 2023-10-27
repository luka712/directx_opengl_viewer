#pragma once

#include "Renderer.hpp"
#include "Texture2D.hpp"

namespace Viewer
{
	class RenderTarget
	{
	private:

		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		CComPtr<ID3D11RenderTargetView> m_renderTargetView;

		CComPtr<ID3D11Texture2D> m_depthStencilTexture;
		CComPtr<ID3D11DepthStencilView> m_depthStencilView;

		Texture2D* m_texture;

		Renderer& m_renderer;

		unsigned int m_width;
		unsigned int m_height;

	public:

		Texture2D& GetTexture() const { return *m_texture; }


		RenderTarget(
			CComPtr<ID3D11Device> device,
			CComPtr<ID3D11DeviceContext> deviceContext, 
			Renderer& renderer,
			unsigned int width, 
			unsigned int height);
		void Initialize();
		void Use();
		void Stop();

		bool ConfigureDepthStencil();
	};
}