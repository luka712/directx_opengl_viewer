#include "material/UnlitMaterial.hpp"
#include "camera/Camera.hpp"

namespace Viewer
{
	UnlitMaterial::UnlitMaterial()
	{
		m_materialShader = new UnlitMaterialShader();
		m_materialBuffer = new UniformBuffer<UnlitMaterialData>();
		m_textureTillingBuffer = new UniformBuffer<glm::vec2>();

        DiffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
		DiffuseTexture = nullptr;
		TextureTilling = glm::vec2(1.0f, 1.0f);
	}

	UnlitMaterial::~UnlitMaterial()
	{
		delete m_materialShader;
	}

	void UnlitMaterial::Initialize()
	{
		m_materialShader->Initialize();
		UnlitMaterialData materialData;
        materialData.DiffuseColor = DiffuseColor;
        materialData.Intensity = Intensity;
		m_materialBuffer->Initialize(&materialData);
		m_textureTillingBuffer->Initialize(&TextureTilling);
	}

	void UnlitMaterial::Use()
	{
		m_materialShader->Use();
	}

	void UnlitMaterial::UpdateSelfProperties()
	{
		// Get currently assigned or empty.
		Texture2D* diffuseTexture = DiffuseTexture;

		if (diffuseTexture == nullptr)
		{
			diffuseTexture = Texture2D::GetEmptyTexture();
		}
	

		// update textures.
		m_materialShader->SetDiffuseTexture(*diffuseTexture);

		// update non texture data.
		UnlitMaterialData data;
        data.DiffuseColor = DiffuseColor;
        data.Intensity = Intensity;
		m_materialBuffer->Update(&data);
		m_materialShader->SetMaterial(*m_materialBuffer);

		// update tilling.
		m_textureTillingBuffer->Update(&TextureTilling);
		m_materialShader->SetTextureTilling(*m_textureTillingBuffer);
	}

	void UnlitMaterial::UpdateCameraProperties(Camera& camera)
	{
		m_materialShader->SetCamera(camera.GetCameraBuffer());
	}

	void UnlitMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_materialShader->SetTransform(transform.GetTransformBuffer());
	}
}