#include "shader/RefractionMaterialShader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>

namespace Viewer
{
    RefractionMaterialShader::RefractionMaterialShader()
        : Shader("shaders/RefractionMaterialVS.glsl", "shaders/RefractionMaterialFS.glsl")
    {
    }

    bool RefractionMaterialShader::Initialize()
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

    void RefractionMaterialShader::SetCamera(UniformBuffer<CameraData> &uniformBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.GetBufferID());
    }

    void RefractionMaterialShader::SetTransform(UniformBuffer<glm::mat4> &uniformBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, uniformBuffer.GetBufferID());
    }

    void RefractionMaterialShader::SetMaterial(UniformBuffer<RefractionMaterialData> &materialBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 2, materialBuffer.GetBufferID()); 
    }   

    void RefractionMaterialShader::SetEnvMapTexture(CubeTexture &texture)
    {
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
    }
}