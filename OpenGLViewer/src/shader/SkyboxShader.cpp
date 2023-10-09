#include "shader/SkyboxShader.hpp"

namespace Viewer
{
    SkyboxShader::SkyboxShader()
        : Shader("shaders/SkyboxVS.glsl", "shaders/SkyboxFS.glsl")
    {
        m_textureLocation = 0;
    }

    bool SkyboxShader::Initialize()
    {
        bool initialized = Shader::Initialize();

        if (!initialized)
        {
            return false;
        }

        m_textureLocation = GetUniformLocation("u_cubeTexture");
        return true;
    }

    void SkyboxShader::SetCamera(UniformBuffer<glm::mat4x4> &uniformBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.GetBufferID());
    }

    void SkyboxShader::SetTexture(CubeTexture &texture)
    {
        glUniform1i(m_textureLocation, 0);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
    }

}