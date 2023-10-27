#include "RefractionMaterial.hpp"
#include <stdexcept>


namespace Viewer
{
	RefractionMaterial::RefractionMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_device(device), m_deviceContext(deviceContext), m_materialBuffer(device, deviceContext)
	{
		m_shader = new RefractionMaterialShader(device, deviceContext);
		RefractionIndex = 1.0f;
		EnvMapTexture = nullptr;
	}

	RefractionMaterial::~RefractionMaterial()
	{
		delete m_shader;
	}

	void RefractionMaterial::Initialize()
	{
		m_shader->Initialize();
		m_materialBuffer.Initialize();
	}

	void RefractionMaterial::Use()
	{
		m_shader->Use();
	}
	void RefractionMaterial::UpdateSelfProperties()
	{
		// Get currently assigned or empty.
		CubeTexture* envMapTexture = EnvMapTexture;

		if (EnvMapTexture == nullptr)
		{
			throw std::runtime_error("EnvMapTexture is null");
		}

		m_shader->SetEnvMapTexture(envMapTexture);

		RefractionMaterialData materialData;
		materialData.RefractionIndex = RefractionIndex;
		m_materialBuffer.Update(materialData);
		m_shader->SetMaterial(m_materialBuffer.GetBuffer());
	}
	void RefractionMaterial::UpdateCameraProperties(Camera& camera)
	{
		m_shader->SetCamera(camera.GetCameraBuffer()->GetBuffer());
	}

	void RefractionMaterial::UpdateTransformProperties(Transform& transform)
	{
		m_shader->SetTransform(transform.GetBuffer().GetBuffer());
	}

}

