#include "Renderer.hpp"
#include "Win32ErrorUtil.hpp"

namespace Viewer
{

	bool Renderer::Initialize(HWND windowHandle, unsigned int Width, unsigned int Height)
	{
		// Create the device, device context, and swap chain
		// Define your swap chain and device creation parameters
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 1;
		sd.BufferDesc.Width = Width;
		sd.BufferDesc.Height = Height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = windowHandle;
		sd.SampleDesc.Count = 1;
		sd.Windowed = TRUE;
		sd.Flags = D3D11_CREATE_DEVICE_DEBUG;

		// Create the Direct3D 11 device and swap chain
		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE, // or D3D_DRIVER_TYPE_WARP for software rendering
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&sd,
			&m_swapChain,
			&m_device,
			nullptr,
			&m_deviceContext
		);

		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed to create device and swap chain", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Get a pointer to the back buffer
		CComPtr<ID3D11Texture2D> backBuffer;
		hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer.p));

		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed to get back buffer", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Create a render target view
		hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView.p);

		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed to create render target view", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!ConfigureDepthStencil(Width, Height))
		{
			MessageBoxW(nullptr, L"Failed to configure depth stencil", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Set the render target view as the current render target
		ID3D11RenderTargetView* renderTargetViewPtr = m_renderTargetView.p;
		ID3D11DepthStencilView* depthStencilViewPtr = m_depthStencilView.p;
		m_deviceContext->OMSetRenderTargets(1, &renderTargetViewPtr, depthStencilViewPtr);

		// Set the viewport
		CD3D11_VIEWPORT viewport = CD3D11_VIEWPORT(
			0.0f,
			0.0f,
			static_cast<float>(Width),
			static_cast<float>(Height)
		);
		m_deviceContext->RSSetViewports(1, &viewport);


		D3D11_RASTERIZER_DESC raster_desc;
		raster_desc.FillMode = D3D11_FILL_SOLID;
		raster_desc.CullMode = D3D11_CULL_BACK;
		raster_desc.FrontCounterClockwise = true;
		raster_desc.DepthBias = 0;
		raster_desc.DepthBiasClamp = 0.0f;
		raster_desc.SlopeScaledDepthBias = 0.0f;
		raster_desc.DepthClipEnable = true;
		raster_desc.ScissorEnable = false;
		raster_desc.MultisampleEnable = false;
		raster_desc.AntialiasedLineEnable = false;

		m_rasterizerState = nullptr;
		hr = m_device->CreateRasterizerState(&raster_desc, &m_rasterizerState.p);

		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed to create rasterizer state", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}




		return true;
	}

	void Renderer::Begin()
	{
		// Raster state 
		m_deviceContext->RSSetState(m_rasterizerState);

		// CLEAR COLOR
		m_deviceContext->ClearRenderTargetView(m_renderTargetView, m_clearColor.m128_f32);

		// CLEAR DEPTH STENCIL
		m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void Renderer::DrawToScreenTexture()
	{
		ID3D11RenderTargetView* renderTargetViewPtr = m_renderTargetView.p;
		ID3D11DepthStencilView* depthStencilViewPtr = m_depthStencilView.p;
		m_deviceContext->OMSetRenderTargets(1, &renderTargetViewPtr, depthStencilViewPtr);
	}


	void Renderer::End()
	{
		// present
		m_swapChain->Present(0, 0);
	}

	void Renderer::ResetRasterizerState()
	{
		m_deviceContext->RSSetState(m_rasterizerState);
	}

	bool Renderer::ConfigureDepthStencil(unsigned int Width, unsigned int Height)
	{
		m_depthStencilTexture = nullptr;
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = Width;
		descDepth.Height = Height;
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