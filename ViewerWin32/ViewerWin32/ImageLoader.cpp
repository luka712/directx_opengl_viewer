#include "ImageLoader.hpp"
#include <Windows.h>
#include <wincodec.h>
#include <atlbase.h> // Contains the declaration of CComPtr.

// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-resources-textures-how-to

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

		// Initialize COM
		CComPtr<IWICImagingFactory> pFactory;
		HRESULT hresult = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory.p));

		if(FAILED(hresult))
		{
			MessageBoxW(nullptr, L"Failed to create IWICImagingFactory", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Create decoder
		CComPtr<IWICBitmapDecoder> pDecoder;
		hresult = pFactory->CreateDecoderFromFilename(CA2W(path.c_str()), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder.p);

		if(FAILED(hresult))
		{
			MessageBoxW(nullptr, L"Failed to create IWICBitmapDecoder", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Get frame
		CComPtr<IWICBitmapFrameDecode> pFrame;
		hresult = pDecoder->GetFrame(0, &pFrame.p);

		if(FAILED(hresult))
		{
			MessageBoxW(nullptr, L"Failed to create IWICBitmapFrameDecode", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Get pixel format
		WICPixelFormatGUID pixelFormat;
		hresult = pFrame->GetPixelFormat(&pixelFormat);

		if(FAILED(hresult))
		{
			MessageBoxW(nullptr, L"Failed to get pixel format", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}


	

		

		


		ImageData* imageData = new ImageData();
		imageData->bytePerPixel = 4;
		imageData->width = image->GetWidth();
		imageData->height = image->GetHeight();
		imageData->data = (unsigned char*)malloc(imageData->width * imageData->height * imageData->bytePerPixel);


	}

