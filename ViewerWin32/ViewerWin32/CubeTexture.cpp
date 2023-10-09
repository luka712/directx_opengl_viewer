#include "CubeTexture.hpp"

namespace Viewer
{

	CubeTexture::CubeTexture(CComPtr<ID3D11Device> device)
		:m_device(device)
	{
	}

	void CubeTexture::Initialize(ImageData& imgDataRight,
		ImageData& imgDataLeft,
		ImageData& imgDataTop,
		ImageData& imgDataBottom,
		ImageData& imgDataBack,
		ImageData& imgDataFront)
	{
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = imgDataRight.Width;
		textureDesc.Height = imgDataRight.Width;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 6;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		D3D11_SUBRESOURCE_DATA initData[6];
		initData[0].pSysMem = imgDataRight.Data;
		initData[0].SysMemPitch = imgDataRight.Width * 4;
		initData[0].SysMemSlicePitch = 0;


		initData[1].pSysMem = imgDataLeft.Data;
		initData[1].SysMemPitch = imgDataLeft.Width * 4;
		initData[1].SysMemSlicePitch = 0;

		initData[2].pSysMem = imgDataTop.Data;
		initData[2].SysMemPitch = imgDataTop.Width * 4;
		initData[2].SysMemSlicePitch = 0;

		initData[3].pSysMem = imgDataBottom.Data;
		initData[3].SysMemPitch = imgDataBottom.Width * 4;
		initData[3].SysMemSlicePitch = 0;

		initData[4].pSysMem = imgDataBack.Data;
		initData[4].SysMemPitch = imgDataBack.Width * 4;
		initData[4].SysMemSlicePitch = 0;

		initData[5].pSysMem = imgDataFront.Data;
		initData[5].SysMemPitch = imgDataFront.Width * 4;
		initData[5].SysMemSlicePitch = 0;


		HRESULT hr = m_device->CreateTexture2D(&textureDesc, &initData[0], &m_texture.p);

		if (FAILED(hr))
		{
			// Handle texture creation failure

			MessageBoxW(nullptr, L"Failed to create texture", L"Error", MB_OK | MB_ICONERROR);
			return;
		}


		// Create the resource view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		hr = m_device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView.p);

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

		hr = m_device->CreateSamplerState(&samplerDesc, &m_samplerState.p);

		if (FAILED(hr))
		{
			// Handle sampler creation failure
			MessageBoxW(nullptr, L"Failed to create sampler", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}



}
