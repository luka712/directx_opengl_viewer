#include "StandardMaterial.hpp"


namespace Viewer
{
	StandardMaterial::StandardMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_device(device), m_deviceContext(deviceContext)
	{
		m_materialShader = new StandardMaterialShader(device, deviceContext);
		m_materialBuffer = new ConstantBuffer<MaterialData>(device, deviceContext);
		DiffuseTexture = nullptr;
		SpecularTexture = nullptr;
		DiffuseCoefficient = 1.0f;
		SpecularCoefficient = 1.0f;
		Shininess = 12.0f;
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
	}
	void StandardMaterial::UpdateCameraProperties(Camera& camera)
	{
		m_materialShader->SetCamera(camera.GetCameraBuffer()->GetBuffer());
	}

	void StandardMaterial::UpdateTransformProperties(ConstantBuffer<DirectX::XMMATRIX> worldMatrixBuffer, ConstantBuffer<DirectX::XMMATRIX> normalMatrixBuffer)
	{
		m_materialShader->SetModelMatrix(worldMatrixBuffer.GetBuffer());
		m_materialShader->SetNormalMatrix(normalMatrixBuffer.GetBuffer());
	}

	void StandardMaterial::UpdateLightsProperties(ConstantBuffer<AmbientLight> ambientLightBuffer, ConstantBuffer<DirectionalLight> directionalLightBuffer, ConstantBuffer<PointLight> pointLightBuffer)
	{
		m_materialShader->SetAmbientLight(ambientLightBuffer.GetBuffer());
		m_materialShader->SetDirectionalLights(directionalLightBuffer.GetBuffer());
		m_materialShader->SetPointLights(pointLightBuffer.GetBuffer());
	}
}

