#include "shader/StandardMaterialShader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>

namespace Viewer
{
	StandardMaterialShader::StandardMaterialShader()
		: Shader("shaders/StandardMaterialVS.glsl", "shaders/StandardMaterialFS.glsl")
	{
	}

	bool StandardMaterialShader::Initialize()
	{
		bool initialized = Shader::Initialize();

		if (!initialized)
		{
			return false;
		}
		// material
		m_diffuseTextureLocation = GetUniformLocation("u_diffuseTexture");
		m_specularTextureLocation = GetUniformLocation("u_specularTexture");

		return true;
	}

	

	void StandardMaterialShader::SetCamera(UniformBuffer<CameraData> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetTransform(UniformBuffer<glm::mat4> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetTextureTilling(UniformBuffer<glm::vec2>& uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetAmbientLight(UniformBuffer<AmbientLight> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 3, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetDirectionalLights(UniformBuffer<DirectionalLight> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 4, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetPointLights(UniformBuffer<PointLight> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 5, uniformBuffer.GetBufferID());
	}

	void StandardMaterialShader::SetMaterial(UniformBuffer<MaterialData> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 6, uniformBuffer.GetBufferID());
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