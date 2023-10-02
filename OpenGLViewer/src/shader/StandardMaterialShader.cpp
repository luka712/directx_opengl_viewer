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

		// matrices
		m_viewProjectionMatrixLocation = GetUniformLocation("u_projectionViewMatrix");
		m_modelMatrixLocation = GetUniformLocation("u_modelMatrix");
		m_normalMatrixLocation = GetUniformLocation("u_normalMatrix");

		// camera
		m_cameraPositionLocation = GetUniformLocation("u_cameraPosition");

		// material
		m_diffuseTextureLocation = GetUniformLocation("u_material.diffuseTexture");
		m_specularTextureLocation = GetUniformLocation("u_material.specularTexture");
		m_diffuseCoefficientLocation = GetUniformLocation("u_material.diffuseCoefficient");
		m_specularCoefficientLocation = GetUniformLocation("u_material.specularCoefficient");
		m_shininessLocation = GetUniformLocation("u_material.shininess");

		// Ambient light
		m_ambientLightIntensityLocation = GetUniformLocation("u_ambientLight.intensity");
		m_ambientLightColorLocation = GetUniformLocation("u_ambientLight.color");

		// Directional lights
		for (size_t i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
		{
			m_directionalLightDirectionLocation[i] = GetUniformLocation(("u_directionalLights[" + std::to_string(i) + "].direction").c_str());
			m_directionalLightIntensityLocation[i] = GetUniformLocation(("u_directionalLights[" + std::to_string(i) + "].intensity").c_str());
			m_directionalLightColorLocation[i] = GetUniformLocation(("u_directionalLights[" + std::to_string(i) + "].color").c_str());
		}

		// Point ligts
		for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			m_pointLightPositionLocation[i] = GetUniformLocation(("u_pointLights[" + std::to_string(i) + "].position").c_str());
			m_pointLightIntensityLocation[i] = GetUniformLocation(("u_pointLights[" + std::to_string(i) + "].intensity").c_str());
			m_pointLightColorLocation[i] = GetUniformLocation(("u_pointLights[" + std::to_string(i) + "].color").c_str());
		}

		return true;
	}

	void StandardMaterialShader::SetModelMatrix(const glm::mat4 &modelMatrix)
	{
		glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	}

	void StandardMaterialShader::SetNormalMatrix(const glm::mat3 &normalMatrix)
	{
		glUniformMatrix3fv(m_normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
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

	void StandardMaterialShader::SetPointLight(size_t index, const glm::vec3 &position, float intensity, const glm::vec3 &color)
	{
		if (index >= MAX_POINT_LIGHTS)
		{
			std::string msg = "Point light index " + std::to_string(index) + " is out of range.";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", msg.c_str(), nullptr);
			return;
		}

		glUniform3fv(m_pointLightPositionLocation[index], 1, glm::value_ptr(position));
		glUniform1f(m_pointLightIntensityLocation[index], intensity);
		glUniform3fv(m_pointLightColorLocation[index], 1, glm::value_ptr(color));
	}

	void StandardMaterialShader::SetDiffuseTexture(Texture2D &texture)
	{
		glUniform1i(m_diffuseTextureLocation, 0);
		glUniform1i(m_specularTextureLocation, 1);

		glActiveTexture(GL_TEXTURE0);
		texture.Bind();
	}

	void StandardMaterialShader::SetSpecularTexture(Texture2D &texture)
	{
		glActiveTexture(GL_TEXTURE1);
		texture.Bind();
	}

	void StandardMaterialShader::SetDiffuseCoefficient(float diffuseCoefficient)
	{
		glUniform1f(m_diffuseCoefficientLocation, diffuseCoefficient);
	}

	void StandardMaterialShader::SetSpecularCoefficient(float specularCoefficient)
	{
		glUniform1f(m_specularCoefficientLocation, specularCoefficient);
	}

	void StandardMaterialShader::SetShininess(float shininess)
	{
		glUniform1f(m_shininessLocation, shininess);
	}

	void StandardMaterialShader::SetCameraPosition(const glm::vec3 &cameraPosition)
	{
		glUniform3fv(m_cameraPositionLocation, 1, glm::value_ptr(cameraPosition));
	}
}