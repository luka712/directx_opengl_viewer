#include "Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Viewer
{
	void Texture2D::Initialize(CComPtr<ID3D11Device> device, std::string filePath)
	{
		// load and create texture
		int width, height, nrChannels;
		unsigned char* stbiData = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

		if (stbiData == nullptr)
		{
			// Handle texture loading failure
			MessageBoxW(nullptr, L"Failed to load image", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		size_t textureByteSize = width * height * 4;
		unsigned char* textureData = (unsigned char*)malloc(textureByteSize);
		// directx does not support 3 channel textures, therefore move to 4 channel
		if (nrChannels == 3)
		{
			size_t i = 0;
			for (size_t j = 0; j < width * height * 3; j += 3)
			{
				textureData[i] = stbiData[j];
				textureData[i + 1] = stbiData[j + 1];
				textureData[i + 2] = stbiData[j + 2];
				textureData[i + 3] = 255;
				i += 4;
			}
		}
		else
		{
			// can be just copied
			memcpy(textureData, stbiData, width * height * 4);
		}

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = textureData;
		initData.SysMemPitch = width * 4;
		initData.SysMemSlicePitch = 0;

		HRESULT hr = device->CreateTexture2D(&textureDesc, &initData, &m_texture.p);

		if (FAILED(hr))
		{
			// Handle texture creation failure
			MessageBoxW(nullptr, L"Failed to create texture", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		// Create the resource view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		hr = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView.p);

		if (FAILED(hr))
		{
			// Handle resource view creation failure
			MessageBoxW(nullptr, L"Failed to create resource view", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		ID3D11SamplerState* pSamplerState = m_samplerState.p;
		hr = device->CreateSamplerState(&samplerDesc, &pSamplerState);

		if (FAILED(hr))
		{
			// Handle sampler creation failure
			MessageBoxW(nullptr, L"Failed to create sampler", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		free(textureData);
		stbi_image_free(stbiData);
	}
}