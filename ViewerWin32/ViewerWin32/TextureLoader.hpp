#pragma once

#include "Texture2D.hpp"
#include "CubeTexture.hpp"
#include <string>

namespace Viewer
{
	class TextureLoader
	{
	private:
		CComPtr<ID3D11Device> m_device;

	public:
		TextureLoader(CComPtr<ID3D11Device> device);

		/// <summary>
		/// Loads the texture from the image file.
		/// </summary>
		/// <returns></returns>
		Texture2D* LoadFromImg(std::string imgFilepath);
	

		CubeTexture* LoadFromImg(std::string rightImgFilePath,
			std::string leftImgFilePath,
			std::string topImgFilePath,
			std::string bottomImgFilePath,
			std::string backImgFilePath,
			std::string frontImgFilePath);
	};
}