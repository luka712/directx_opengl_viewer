#include "shader/ReflectiveMaterialShader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>

namespace Viewer
{
    ReflectiveMaterialShader::ReflectiveMaterialShader()
        : Shader("shaders/ReflectiveMaterialVS.glsl", "shaders/ReflectiveMaterialFS.glsl")
    {
    }

    bool ReflectiveMaterialShader::Initialize()
    {
        bool initialized = Shader::Initialize();

        if (!initialized)
        {
            return false;
        }
        // material
        m_cubeTextureLocation = GetUniformLocation("u_cubeTexture");

        return true;
    }

    void ReflectiveMaterialShader::SetCamera(UniformBuffer<CameraData> &uniformBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.GetBufferID());
    }

    void ReflectiveMaterialShader::SetTransform(UniformBuffer<glm::mat4> &uniformBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, uniformBuffer.GetBufferID());
    }

    void ReflectiveMaterialShader::SetEnvMapTexture(CubeTexture &texture)
    {
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
    }
}