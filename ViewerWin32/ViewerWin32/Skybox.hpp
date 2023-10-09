#pragma once

#include "CubeTexture.hpp"
#include "Camera.hpp"
#include "GeometryBuffer.hpp"
#include "SkyboxShader.hpp"
#include "Renderer.hpp"

namespace Viewer
{
	class Skybox
	{
	private:
		Renderer& m_renderer;
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;
		CComPtr< ID3D11DepthStencilState> m_depthStencilState;
		CComPtr< ID3D11RasterizerState> m_rasterizerState;

		GeometryBuffer m_geometryBuffer;
		SkyboxShader m_shader;

	public:
		Skybox(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Renderer& renderer);
		CubeTexture* SkyTexture;

		void Initialize();
		void Draw(Camera& camera);

	};
}