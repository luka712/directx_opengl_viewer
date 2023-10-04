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
		m_modelMatrixLocation = GetUniformLocation("u_modelMatrix");
		m_normalMatrixLocation = GetUniformLocation("u_normalMatrix");

		// material
		m_diffuseTextureLocation = GetUniformLocation("u_diffuseTexture");
		m_specularTextureLocation = GetUniformLocation("u_specularTexture");

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

	void StandardMaterialShader::SetCamera(UniformBuffer<CameraData> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetAmbientLight(UniformBuffer<AmbientLight> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetDirectionalLights(UniformBuffer<DirectionalLight> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetPointLights(UniformBuffer<PointLight> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 3, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetMaterial(UniformBuffer<MaterialData> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 4, uniformBuffer.GetBufferID());
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

}