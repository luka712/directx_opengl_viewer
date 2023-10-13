#include "shader/DebugNormalShader.hpp"

namespace Viewer
{
    DebugNormalShader::DebugNormalShader()
        : Shader("shaders/DebugNormalVS.glsl", "shaders/DebugNormalFS.glsl", "shaders/DebugNormalGS.glsl")
    {
    }

    bool DebugNormalShader::Initialize()
    {
        bool initialized = Shader::Initialize();

        if (!initialized)
        {
            return false;
        }

        return true;
    }

    void DebugNormalShader::SetProjectionMatrix(UniformBuffer<glm::mat4x4>& uniformBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.GetBufferID());
    }

    void DebugNormalShader::SetViewModelMatrix(UniformBuffer<ViewModelViewModelNormalData> &uniformBuffer)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, uniformBuffer.GetBufferID());
    }



}