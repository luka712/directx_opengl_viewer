#include "material/RefractionMaterial.hpp"
#include "camera/Camera.hpp"
#include <stdexcept>

namespace Viewer
{
	RefractionMaterial::RefractionMaterial()
	{
		m_materialShader = new RefractionMaterialShader();
        EnvMapTexture = nullptr;
	}

	RefractionMaterial::~RefractionMaterial()
	{
		delete m_materialShader;
	}

	void RefractionMaterial::Initialize()
	{
		m_materialShader->Initialize();
        m_materialBuffer.Initialize();
	}

	void RefractionMaterial::Use()
	{
		m_materialShader->Use();
	}

	void RefractionMaterial::UpdateSelfProperties()
	{
		// Get currently assigned or empty.
		CubeTexture* envMapTexture = EnvMapTexture;
		
		if(EnvMapTexture == nullptr)
		{
			throw std::runtime_error("EnvMapTexture is null");
		}

		// update textures.
		m_materialShader->SetEnvMapTexture(*envMapTexture);
        
        RefractionMaterialData data;
        data.RefractionIndex = RefractionIndex;
        m_materialBuffer.Update(&data, 1);
	}

	void RefractionMaterial::UpdateProperties(Camera& camera)
	{
		m_materialShader->SetCamera(camera.GetCameraBuffer());
	}

	void RefractionMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_materialShader->SetTransform(transform.GetTransformBuffer());
	}
}