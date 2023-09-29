#include "loaders/ImageLoader.hpp"

#include <SDL_image.h>
#include <stdexcept>

namespace Viewer
{
	ImageData::~ImageData()
	{
		if (data != nullptr)
		{
			delete[] data;
		}
	}

	ImageData* ImageLoader::LoadImage(std::string path)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		if (surface == nullptr || (surface->w == 0 && surface->h == 0))
		{
			std::string error = "Failed to load image: ";
			error += IMG_GetError();

			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Image Loader Error", error.c_str(), nullptr);
			return nullptr;
		}
	
		size_t bytePerPixel = surface->format->BytesPerPixel;

		ImageData* imageData = new ImageData();
		// Allocate memory for the image data
		size_t byteSize = surface->w * surface->h * bytePerPixel;
		imageData->bytePerPixel = bytePerPixel;
		imageData->data = (unsigned char*)malloc(byteSize);
		imageData->width = surface->w;
		imageData->height = surface->h;

		// Copy the pixels from the surface to the imageData
		memcpy(imageData->data, surface->pixels, byteSize);


	    SDL_FreeSurface(surface);
		return imageData;
	}
}