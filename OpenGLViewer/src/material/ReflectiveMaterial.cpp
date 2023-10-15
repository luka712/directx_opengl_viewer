#include "material/ReflectiveMaterial.hpp"
#include "camera/Camera.hpp"
#include <stdexcept>

namespace Viewer
{
	ReflectiveMaterial::ReflectiveMaterial()
	{
		m_materialShader = new ReflectiveMaterialShader();
        EnvMapTexture = nullptr;
	}

	ReflectiveMaterial::~ReflectiveMaterial()
	{
		delete m_materialShader;
	}

	void ReflectiveMaterial::Initialize()
	{
		m_materialShader->Initialize();
	}

	void ReflectiveMaterial::Use()
	{
		m_materialShader->Use();
	}

	void ReflectiveMaterial::UpdateSelfProperties()
	{
		// Get currently assigned or empty.
		CubeTexture* envMapTexture = EnvMapTexture;
		
		if(EnvMapTexture == nullptr)
		{
			throw std::runtime_error("EnvMapTexture is null");
		}

		// update textures.
		m_materialShader->SetEnvMapTexture(*envMapTexture);
	}

	void ReflectiveMaterial::UpdateProperties(Camera& camera)
	{
		m_materialShader->SetCamera(camera.GetCameraBuffer());
	}

	void ReflectiveMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_materialShader->SetTransform(transform.GetTransformBuffer());
	}
}