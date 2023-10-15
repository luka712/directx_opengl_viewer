#include "Skybox.hpp"
#include "Geometry.hpp"
#

namespace Viewer
{
	Skybox::Skybox(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Renderer& renderer)
		: m_device(device),
		m_deviceContext(deviceContext),
		m_geometryBuffer(device, deviceContext),
		m_shader(device, deviceContext),
		m_renderer(renderer)
	{
	}

	void Skybox::Initialize()
	{
		Geometry geometry = Geometry::CreateSkyboxGeometry();
		m_geometryBuffer.Initialize(geometry.positionVertices, geometry.indices, geometry.textureVertices, geometry.normalVertices, geometry.colorVertices);
		m_shader.Initialize();

		// Create a depth stencil state for the skybox
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		depthStencilDesc.DepthEnable = true;                 
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		depthStencilDesc.StencilEnable = false;

		HRESULT hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState.p);

		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed to create depth stencil state", L"Error", MB_OK | MB_ICONERROR);
			return;
		}


		D3D11_RASTERIZER_DESC raster_desc;
		raster_desc.FillMode = D3D11_FILL_SOLID;
		raster_desc.CullMode = D3D11_CULL_NONE; //D3D11_CULL_FRONT;
		raster_desc.FrontCounterClockwise = true;
		raster_desc.DepthBias = 0;
		raster_desc.DepthBiasClamp = 0.0f;
		raster_desc.SlopeScaledDepthBias = 0.0f;
		raster_desc.DepthClipEnable = false;
		raster_desc.ScissorEnable = false;
		raster_desc.MultisampleEnable = false;
		raster_desc.AntialiasedLineEnable = false;

		m_rasterizerState = nullptr;
		hr = m_device->CreateRasterizerState(&raster_desc, &m_rasterizerState.p);

		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed to create rasterizer state", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	void Skybox::Draw(Camera& camera)
	{
		// Disable depth testing
		m_deviceContext->RSSetState(m_rasterizerState);
		m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 0);
		m_shader.Use();
		m_shader.SetCamera(camera.GetSkyboxCameraBuffer()->GetBuffer());
		m_shader.SetTexture(SkyTexture);
		m_geometryBuffer.Draw();
		// Re-enable depth testing
		m_deviceContext->OMSetDepthStencilState(nullptr, 0);
		m_renderer.ResetRasterizerState();

	}
}
