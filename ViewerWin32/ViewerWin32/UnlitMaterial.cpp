#include "UnlitMaterial.hpp"


namespace Viewer
{
	UnlitMaterial::UnlitMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_device(device), m_deviceContext(deviceContext)
	{
		m_materialShader = new UnlitMaterialShader(device, deviceContext);
		m_materialBuffer = new ConstantBuffer<UnlitMaterialData>(device, deviceContext);
		m_textureTillingBuffer = new ConstantBuffer<DirectX::XMFLOAT2>(device, deviceContext);
		DiffuseTexture = nullptr;
		TextureTilling = DirectX::XMFLOAT2(1.0f, 1.0f);
		DiffuseColor = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		Intensity = 1;
	}

	UnlitMaterial::~UnlitMaterial()
	{
		delete m_materialShader;
		delete m_materialBuffer;
	}

	void UnlitMaterial::Initialize()
	{
		m_materialShader->Initialize();
		m_materialBuffer->Initialize();
		m_textureTillingBuffer->Initialize();
	}

	void UnlitMaterial::Use()
	{
		m_materialShader->Use();
	}
	void UnlitMaterial::UpdateSelfProperties()
	{
		Texture2D* diffuseTexture = DiffuseTexture;
		if (diffuseTexture == nullptr)
		{
			diffuseTexture = Texture2D::GetEmptyTexture(m_device);
		}


		m_materialShader->SetDiffuseTexture(diffuseTexture);

		UnlitMaterialData materialData;
		materialData.Color = DiffuseColor;
		materialData.Intensity = Intensity;
		m_materialBuffer->Update(materialData);
		m_materialShader->SetMaterial(*m_materialBuffer);

		// set texture tilling.
		m_textureTillingBuffer->Update(TextureTilling);
		m_materialShader->SetTextureTilling(m_textureTillingBuffer->GetBuffer());
	}
	void UnlitMaterial::UpdateCameraProperties(Camera& camera)
	{
		m_materialShader->SetCamera(camera.GetCameraBuffer()->GetBuffer());
	}

	void UnlitMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_materialShader->SetTransform(transform.GetBuffer().GetBuffer());
	}
}

