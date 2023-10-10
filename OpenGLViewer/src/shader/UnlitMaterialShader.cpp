#include "shader/UnlitMaterialShader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>

namespace Viewer
{
	UnlitMaterialShader::UnlitMaterialShader()
		: Shader("shaders/UnlitMaterialVS.glsl", "shaders/UnlitMaterialFS.glsl")
	{
	}

	bool UnlitMaterialShader::Initialize()
	{
		bool initialized = Shader::Initialize();

		if (!initialized)
		{
			return false;
		}
		// material
		m_diffuseTextureLocation = GetUniformLocation("u_diffuseTexture");

		return true;
	}

	

	void UnlitMaterialShader::SetCamera(UniformBuffer<CameraData> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.GetBufferID());
	}

	void UnlitMaterialShader::SetTransform(UniformBuffer<glm::mat4> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, uniformBuffer.GetBufferID());
	}

	void UnlitMaterialShader::SetTextureTilling(UniformBuffer<glm::vec2>& uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, uniformBuffer.GetBufferID());
	}

	void UnlitMaterialShader::SetMaterial(UniformBuffer<UnlitMaterialData> &uniformBuffer)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 3, uniformBuffer.GetBufferID());
	}


	void UnlitMaterialShader::SetDiffuseTexture(Texture2D &texture)
	{
		glUniform1i(m_diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		texture.Bind();
	}
}