#ifndef DEBUG_NORMAL_SHADER_HPP

#define DEBUG_NORMAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>
#include "buffer/UniformBuffer.hpp"
#include "texture/CubeTexture.hpp"
#include "camera/Camera.hpp"

namespace Viewer
{
    struct ViewModelViewModelNormalData
    {
        glm::mat4x4 ViewModelMatrix;
        glm::mat4x4 ViewModelNormalMatrix;
    };

    class DebugNormalShader final : public Shader
    {
    public:
        DebugNormalShader();
        bool Initialize();


        /// @brief Sets the model matrix value of camera.
        /// @param modelBuffer - The buffer containing the model matrix value of camera.
        void SetViewModelMatrix(UniformBuffer<ViewModelViewModelNormalData> &modelBuffer);

        /// @brief Sets the projection matrix value of camera.
        /// @param projectionBuffer - The buffer containing the projection matrix value of camera.
        void SetProjectionMatrix(UniformBuffer<glm::mat4x4> &projectionBuffer);
    };
}

#endif