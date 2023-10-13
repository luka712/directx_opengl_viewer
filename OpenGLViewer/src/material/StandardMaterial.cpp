#include "material/StandardMaterial.hpp"
#include "camera/Camera.hpp"

namespace Viewer
{
	StandardMaterial::StandardMaterial()
	{
		m_materialShader = new StandardMaterialShader();
		m_materialBuffer = new UniformBuffer<PhongMaterialData>();
		m_textureTillingBuffer = new UniformBuffer<glm::vec2>();

		DiffuseTexture = nullptr;
		SpecularTexture = nullptr;
		DiffuseCoefficient = 1.0f;
		SpecularCoefficient = 1.0f;
		Shininess = 32.0f;
		TextureTilling = glm::vec2(1.0f, 1.0f);
	}

	StandardMaterial::~StandardMaterial()
	{
		delete m_materialShader;
	}

	void StandardMaterial::Initialize()
	{
		m_materialShader->Initialize();
		PhongMaterialData materialData;
		m_materialBuffer->Initialize(&materialData);

		m_textureTillingBuffer->Initialize(&TextureTilling);
	}

	void StandardMaterial::Use()
	{
		m_materialShader->Use();
	}

	void StandardMaterial::UpdateSelfProperties()
	{
		// Get currently assigned or empty.
		Texture2D* diffuseTexture = DiffuseTexture;
		Texture2D* specularTexture = SpecularTexture;
		if (diffuseTexture == nullptr)
		{
			diffuseTexture = Texture2D::GetEmptyTexture();
		}
		if (specularTexture == nullptr)
		{
			specularTexture = Texture2D::GetEmptyTexture();
		}

		// update textures.
		m_materialShader->SetDiffuseTexture(*diffuseTexture);
		m_materialShader->SetSpecularTexture(*specularTexture);

		// update non texture data.
		PhongMaterialData data;
		data.DiffuseCoefficient = DiffuseCoefficient;
		data.SpecularCoefficient = SpecularCoefficient;
		data.Shininess = Shininess;
		m_materialBuffer->Update(&data);
		m_materialShader->SetMaterial(*m_materialBuffer);

		// update tilling.
		m_textureTillingBuffer->Update(&TextureTilling);
		m_materialShader->SetTextureTilling(*m_textureTillingBuffer);
	}

	void StandardMaterial::UpdateProperties(Camera& camera)
	{
		m_materialShader->SetCamera(camera.GetCameraBuffer());
	}

	void StandardMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_materialShader->SetTransform(transform.GetTransformBuffer());
	}

	void StandardMaterial::UpdateLightsProperties(SceneLights& sceneLights)
	{
		m_materialShader->SetAmbientLight(sceneLights.GetAmbientLightBuffer());
		m_materialShader->SetDirectionalLights(sceneLights.GetDirectionalLightsBuffer());
		m_materialShader->SetPointLights(sceneLights.GetPointLightsBuffer());
	}
}