#include "material/DebugNormalMaterial.hpp"
#include "camera/Camera.hpp"

namespace Viewer
{
	DebugNormalMaterial::DebugNormalMaterial()
	{
		m_shader = new DebugNormalShader();
	}

	DebugNormalMaterial::~DebugNormalMaterial()
	{
		delete m_shader;
	}

	void DebugNormalMaterial::Initialize()
	{
		m_shader->Initialize();
		m_viewModelBuffer.Initialize();
	}

	void DebugNormalMaterial::Use()
	{
		m_shader->Use();
	}

	void DebugNormalMaterial::UpdateProperties(Camera& camera, Transform& transform)
	{
		ViewModelViewModelNormalData data;
		data.ViewModelMatrix = camera.ViewMatrix * transform.ModelMatrix;
		data.ViewModelNormalMatrix = glm::transpose(glm::inverse(data.ViewModelMatrix));
		m_viewModelBuffer.Update(&data, 1);

		m_shader->SetViewModelMatrix(m_viewModelBuffer);
        m_shader->SetProjectionMatrix(camera.GetProjectionBuffer());
	}

	
}