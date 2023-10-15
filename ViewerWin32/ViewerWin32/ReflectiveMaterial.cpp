#include "ReflectiveMaterial.hpp"
#include <stdexcept>


namespace Viewer
{
	ReflectiveMaterial::ReflectiveMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_device(device), m_deviceContext(deviceContext)
	{
		m_shader = new ReflectiveMaterialShader(device, deviceContext);
	}

	ReflectiveMaterial::~ReflectiveMaterial()
	{
		delete m_shader;
	}

	void ReflectiveMaterial::Initialize()
	{
		m_shader->Initialize();
	}

	void ReflectiveMaterial::Use()
	{
		m_shader->Use();
	}
	void ReflectiveMaterial::UpdateSelfProperties()
	{
		// Get currently assigned or empty.
		CubeTexture* envMapTexture = EnvMapTexture;

		if (EnvMapTexture == nullptr)
		{
			throw std::runtime_error("EnvMapTexture is null");
		}

		m_shader->SetEnvMapTexture(envMapTexture);
	}
	void ReflectiveMaterial::UpdateCameraProperties(Camera& camera)
	{
		m_shader->SetCamera(camera.GetCameraBuffer()->GetBuffer());
	}

	void ReflectiveMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_shader->SetTransform(transform.GetBuffer().GetBuffer());
	}

}

