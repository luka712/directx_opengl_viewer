#pragma once

#include <d3d11.h>
#include <string>
#include <atlbase.h> // Contains the declaration of CComPtr.

namespace Viewer
{
	class Texture2D
	{
	public:
		void Initialize(CComPtr<ID3D11Device> device, std::string filePath);

		/// <summary>
		/// Gets the texture.
		/// </summary>
		ID3D11Texture2D* GetTexture() { return m_texture; }

		/// <summary>
		/// Gets the texture view.
		/// </summary>
		/// <returns></returns>
		ID3D11ShaderResourceView* GetTextureView() { return m_textureView; }

		/// <summary>
		/// Gets the sampler state.
		/// </summary>
		ID3D11SamplerState* GetSamplerState() { return m_samplerState; }

	private:
		CComPtr<ID3D11Texture2D> m_texture;
		CComPtr<ID3D11ShaderResourceView> m_textureView;
		CComPtr<ID3D11SamplerState> m_samplerState;

	};
}