#include "TextureLoader.hpp"

namespace Viewer
{
	TextureLoader::TextureLoader(CComPtr<ID3D11Device> device)
		: m_device(device)
	{
	}
	Texture2D* TextureLoader::LoadFromImg(std::string imgFilepath)
	{
		Viewer::ImageLoader imageLoader;
		Viewer::ImageData* imageData = imageLoader.Load(imgFilepath);
		Viewer::Texture2D* texture = new Viewer::Texture2D(m_device);
		texture->Initialize(imageData->Data, imageData->Width, imageData->Height);

		delete imageData;

		return texture;
	}


	CubeTexture* TextureLoader::LoadFromImg(std::string rightImgFilePath, std::string leftImgFilePath, std::string topImgFilePath, std::string bottomImgFilePath, std::string backImgFilePath, std::string frontImgFilePath)
	{
		Viewer::ImageLoader imageLoader;


		Viewer::ImageData* rightImData = imageLoader.Load(rightImgFilePath);
		Viewer::ImageData* leftImData = imageLoader.Load(leftImgFilePath);
		Viewer::ImageData* topImData = imageLoader.Load(topImgFilePath);
		Viewer::ImageData* bottomImData = imageLoader.Load(bottomImgFilePath);
		Viewer::ImageData* backImData = imageLoader.Load(backImgFilePath);
		Viewer::ImageData* frontImData = imageLoader.Load(frontImgFilePath);

		Viewer::CubeTexture* texture = new Viewer::CubeTexture(m_device);
		texture->Initialize(*rightImData, *leftImData, *topImData, *bottomImData, *backImData, *frontImData);

		delete rightImData;
		delete leftImData;
		delete topImData;
		delete bottomImData;
		delete backImData;
		delete frontImData;

		return texture;

	}
}
