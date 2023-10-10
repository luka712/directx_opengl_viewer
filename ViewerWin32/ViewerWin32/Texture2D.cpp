#include "Texture2D.hpp"

namespace Viewer
{

	Texture2D::Texture2D(CComPtr<ID3D11Device> device)
		: m_device(device)
	{
	}

	void Texture2D::Initialize(unsigned char* data, unsigned int width, unsigned int height)
	{
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
		initData.pSysMem = data;
		initData.SysMemPitch = width * 4;
		initData.SysMemSlicePitch = 0;

		HRESULT hr = m_device->CreateTexture2D(&textureDesc, &initData, &m_texture.p);

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
	Texture2D* Texture2D::GetEmptyTexture(CComPtr<ID3D11Device> device)
	{
		static Texture2D* emptyTexture = nullptr;
		if (emptyTexture == nullptr)
		{
			emptyTexture = new Texture2D(device);
			unsigned char data[4] = { 255, 255, 255, 255 };
			emptyTexture->Initialize(&data[0], 1, 1);
		}

		return emptyTexture;
	}
}