#include "StandardMaterial.hpp"


namespace Viewer
{
	StandardMaterial::StandardMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_device(device), m_deviceContext(deviceContext)
	{
		m_materialShader = new StandardMaterialShader(device, deviceContext);
		m_materialBuffer = new ConstantBuffer<MaterialData>(device, deviceContext);
		m_textureTillingBuffer = new ConstantBuffer<DirectX::XMFLOAT2>(device, deviceContext);
		DiffuseTexture = nullptr;
		SpecularTexture = nullptr;
		DiffuseCoefficient = 1.0f;
		SpecularCoefficient = 1.0f;
		Shininess = 12.0f;
		TextureTilling = DirectX::XMFLOAT2(1.0f, 1.0f);
	}

	StandardMaterial::~StandardMaterial()
	{
		delete m_materialShader;
		delete m_materialBuffer;
	}

	void StandardMaterial::Initialize()
	{
		//std::vector<unsigned char> data = { 255, 255, 255, 255 };
		//m_emptyTexture = new Texture2D(m_device, data, 1, 1);
		//m_emptyTexture->Initialize();

		m_materialShader->Initialize();
		m_materialBuffer->Initialize();
		m_textureTillingBuffer->Initialize();
	}

	void StandardMaterial::Use()
	{
		m_materialShader->Use();
	}
	void StandardMaterial::UpdateSelfProperties()
	{
		Texture2D* diffuseTexture = DiffuseTexture;
		Texture2D* specularTexture = SpecularTexture;
		if (diffuseTexture == nullptr)
		{
			diffuseTexture = m_emptyTexture;
		}
		if (specularTexture == nullptr)
		{
			specularTexture = m_emptyTexture;
		}

		m_materialShader->SetDiffuseTexture(diffuseTexture);
		m_materialShader->SetSpecularTexture(specularTexture);

		MaterialData materialData;
		materialData.DiffuseCoefficient = DiffuseCoefficient;
		materialData.SpecularCoefficient = SpecularCoefficient;
		materialData.Shininess = Shininess;
		m_materialBuffer->Update(materialData);
		m_materialShader->SetMaterial(*m_materialBuffer);

		// set texture tilling.
		m_textureTillingBuffer->Update(TextureTilling);	
		m_materialShader->SetTextureTilling(m_textureTillingBuffer->GetBuffer());
	}
	void StandardMaterial::UpdateCameraProperties(Camera& camera)
	{
		m_materialShader->SetCamera(camera.GetCameraBuffer()->GetBuffer());
	}

	void StandardMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_materialShader->SetTransform(transform.GetBuffer().GetBuffer());
	}

	void StandardMaterial::UpdateLightsProperties(SceneLights& sceneLights)
	{
		m_materialShader->SetAmbientLight(sceneLights.GetAmbientLightBuffer().GetBuffer());
		m_materialShader->SetDirectionalLights(sceneLights.GetDirectionalLightsBuffer().GetBuffer());
		m_materialShader->SetPointLights(sceneLights.GetPointLightsBuffer().GetBuffer());
	}
}

