#include "ImageLoader.hpp"
#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-resources-textures-how-to

namespace Viewer
{
	
	ImageData::~ImageData()
	{
		if (Data != nullptr)
		{
			delete[] Data;
		}
	}

	ImageData* ImageLoader::Load(std::string filePath)
	{
		ImageData* imageData = new ImageData();

		// load and create texture
		int Width, Height, nrChannels;
		unsigned char* stbiData = stbi_load(filePath.c_str(), &Width, &Height, &nrChannels, 0);

		if (stbiData == nullptr)
		{
			// Handle texture loading failure
			MessageBoxW(nullptr, L"Failed to load image", L"Error", MB_OK | MB_ICONERROR);
			return nullptr;
		}

		size_t textureByteSize = Width * Height * 4;
		imageData->Data = (unsigned char*)malloc(textureByteSize);
		// directx does not support 3 channel textures, therefore move to 4 channel
		if (nrChannels == 3)
		{
			size_t i = 0;
			for (size_t j = 0; j < Width * Height * 3; j += 3)
			{
				imageData->Data[i] = stbiData[j];
				imageData->Data[i + 1] = stbiData[j + 1];
				imageData->Data[i + 2] = stbiData[j + 2];
				imageData->Data[i + 3] = 255;
				i += 4;
			}
		}
		else
		{
			// can be just copied
			memcpy(imageData->Data, stbiData, Width * Height * 4);
		}

		imageData->Width = Width;
		imageData->Height = Height;
		imageData->bytePerPixel = 4;


		// stbi_image_free(stbiData);
		
		return imageData;
	}
}

