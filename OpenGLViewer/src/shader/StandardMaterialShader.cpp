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

		m_viewProjectionMatrixLocation = glGetUniformLocation(m_programId, "u_projectionViewMatrix");
		if (m_viewProjectionMatrixLocation == -1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to get view projection matrix location.", nullptr);
			return false;
		}

		m_modelMatrixLocation = glGetUniformLocation(m_programId, "u_modelMatrix");
		if (m_modelMatrixLocation == -1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to get model matrix location.", nullptr);
			return false;
		}

		m_ambientLightIntensityLocation = glGetUniformLocation(m_programId, "u_ambientLight.intensity");
		if (m_ambientLightIntensityLocation == -1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to get ambient light intensity location.", nullptr);
			return false;
		}

		m_ambientLightColorLocation = glGetUniformLocation(m_programId, "u_ambientLight.color");
		if (m_ambientLightColorLocation == -1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to get ambient light color location.", nullptr);
			return false;
		}

		for (size_t i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
		{
			m_directionalLightDirectionLocation[i] = glGetUniformLocation(m_programId, ("u_directionalLights[" + std::to_string(i) + "].direction").c_str());
			if (m_directionalLightDirectionLocation[i] == -1)
			{
				std::string msg = "Failed to get directional light direction location for light " + std::to_string(i);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", msg.c_str(), nullptr);
				return false;
			}

			m_directionalLightIntensityLocation[i] = glGetUniformLocation(m_programId, ("u_directionalLights[" + std::to_string(i) + "].intensity").c_str());
			if (m_directionalLightIntensityLocation[i] == -1)
			{
				std::string msg = "Failed to get directional light intensity location for light " + std::to_string(i);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", msg.c_str(), nullptr);
				return false;
			}

			m_directionalLightColorLocation[i] = glGetUniformLocation(m_programId, ("u_directionalLights[" + std::to_string(i) + "].color").c_str());
			if (m_directionalLightColorLocation[i] == -1)
			{
				std::string msg = "Failed to get directional light color location for light " + std::to_string(i);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", msg.c_str(), nullptr);
				return false;
			}
		}

		return true;
	}

	void StandardMaterialShader::SetModelMatrix(const glm::mat4 &modelMatrix)
	{
		glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	}

	void StandardMaterialShader::SetProjectionViewMatrix(const glm::mat4 &viewProjectionMatrix)
	{
		glUniformMatrix4fv(m_viewProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
	}

	void StandardMaterialShader::SetAmbientLight(float intensity, const glm::vec3 &color)
	{
		glUniform1f(m_ambientLightIntensityLocation, intensity);
		glUniform3fv(m_ambientLightColorLocation, 1, glm::value_ptr(color));
	}

	void StandardMaterialShader::SetDirectionalLight(size_t index, const glm::vec3 &direction, float intensity, const glm::vec3 &color)
	{
		if (index >= MAX_DIRECTIONAL_LIGHTS)
		{
			std::string msg = "Directional light index " + std::to_string(index) + " is out of range.";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", msg.c_str(), nullptr);
			return;
		}

		glUniform3fv(m_directionalLightDirectionLocation[index], 1, glm::value_ptr(direction));
		glUniform1f(m_directionalLightIntensityLocation[index], intensity);
		glUniform3fv(m_directionalLightColorLocation[index], 1, glm::value_ptr(color));
	}
}