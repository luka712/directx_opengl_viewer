#pragma once

#include <d3d11.h>
#include <string>
#include <atlbase.h> // Contains the declaration of CComPtr.
#include "ImageLoader.hpp"

namespace Viewer
{
	class CubeTexture
	{
	private:
	private:
		CComPtr<ID3D11Device> m_device;

		CComPtr<ID3D11Texture2D> m_texture;
		CComPtr<ID3D11ShaderResourceView> m_textureView;
		CComPtr<ID3D11SamplerState> m_samplerState;

	public:
		/// @brief Create the texture filled with data.
		CubeTexture(CComPtr<ID3D11Device> device);

		/// @brief Initialize the texture.
		void Initialize(ImageData& imgDataRight,
			ImageData& imgDataLeft,
			ImageData& imgDataTop,
			ImageData& imgDataBottom,
			ImageData& imgDataBack,
			ImageData& imgDataFront);

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
	};
}