#include "RenderTarget.hpp"
#include "Win32ErrorUtil.hpp"

namespace Viewer
{
	RenderTarget::RenderTarget(
		CComPtr<ID3D11Device> device,
		CComPtr<ID3D11DeviceContext> deviceContext,
		Renderer& renderer,
		unsigned int width,
		unsigned int height)
		: m_device(device), m_deviceContext(deviceContext), m_renderer(renderer), m_width(width), m_height(height)
	{

	}

	void RenderTarget::Initialize()
	{
		m_texture = new Texture2D(m_device);
		m_texture->Initialize(nullptr, m_width, m_height, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);


		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
		renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // must be same as texture format
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		HRESULT hr = m_device->CreateRenderTargetView(m_texture->GetTexture(), &renderTargetViewDesc, &m_renderTargetView);
		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed to create render target view", L"Error", MB_OK | MB_ICONERROR);
			return;
		}	

		ConfigureDepthStencil();
	}


	void RenderTarget::Use()
	{
		// Bind the render target view and depth/stencil view to the pipeline.
		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView.p, m_depthStencilView.p);


		// Clear the back buffer to a solid color
		float clearColor[4] = { 1, 0,1, 1 };
		m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);

		// Set the viewport
		CD3D11_VIEWPORT viewport = CD3D11_VIEWPORT(
			0.0f,
			0.0f,
			static_cast<float>(m_width),
			static_cast<float>(m_height)
		);
		m_deviceContext->RSSetViewports(1, &viewport);

		// Clear the depth buffer to 1.0 (max depth)
		m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	}

	void RenderTarget::Stop()
	{
		m_renderer.DrawToScreenTexture();
	}

	bool RenderTarget::ConfigureDepthStencil()
	{
		{
			m_depthStencilTexture = nullptr;
			D3D11_TEXTURE2D_DESC descDepth;
			descDepth.Width = m_width;
			descDepth.Height = m_height;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.SampleDesc.Count = 1;
			descDepth.SampleDesc.Quality = 0;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;

			// create a buffer(texture) for the depth stencil
			HRESULT hr = m_device->CreateTexture2D(&descDepth, nullptr, &m_depthStencilTexture.p);

			if (FAILED(hr))
			{
				MessageBoxW(nullptr, L"Failed to create depth stencil texture", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			// Create the depth stencil view
			hr = m_device->CreateDepthStencilView(m_depthStencilTexture, nullptr, &m_depthStencilView.p);

			if (FAILED(hr))
			{
				Win32ErrorUtil::DisplayLastErrorMessage();
				MessageBoxW(nullptr, L"Failed to create depth stencil view", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			return true;
		}
	}
}