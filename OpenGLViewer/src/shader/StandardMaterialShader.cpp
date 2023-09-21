#include "shader/StandardMaterialShader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>

namespace Viewer
{
	StandardMaterialShader::StandardMaterialShader()
		: Shader("shaders/StandardMaterialVShader.glsl", "shaders/StandardMaterialFShader.glsl")
	{
	}

	bool StandardMaterialShader::Initialize()
	{
		bool initialized = Shader::Initialize();

		if (!initialized)
		{
			return false;
		}

		m_viewProjectionMatrixLocation = glGetUniformLocation(m_ID, "u_projectionViewMatrix");

		if (m_viewProjectionMatrixLocation == -1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to get view projection matrix location.", nullptr);
			return false;
		}

		if (m_modelMatrixLocation == -1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to get model matrix location.", nullptr);
			return false;
		}

		m_modelMatrixLocation = glGetUniformLocation(m_ID, "u_modelMatrix");

		return true;
	}

	void StandardMaterialShader::SetModelMatrix(const glm::mat4& modelMatrix)
	{
		glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	}

	void StandardMaterialShader::SetProjectionViewMatrix(const glm::mat4& viewProjectionMatrix)
	{
		glUniformMatrix4fv(m_viewProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
	}
}