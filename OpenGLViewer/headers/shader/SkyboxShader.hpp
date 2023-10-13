#ifndef SKYBOX_SHADER_HPP

#define SKYBOX_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>
#include "buffer/UniformBuffer.hpp"
#include "texture/CubeTexture.hpp"
#include "camera/Camera.hpp"

namespace Viewer
{
    class SkyboxShader final : public Shader
    {
    public:
        SkyboxShader();
        bool Initialize();

        /// @brief Sets the values of the camera.
        /// @param cameraBuffer - The buffer containing the values of the camera.
        void SetCamera(UniformBuffer<glm::mat4x4> &cameraBuffer);

        /// @brief Sets the skybox texture.
        /// @param texture - The texture.
        void SetTexture(CubeTexture &texture);
    private:
        int m_textureLocation;
    };
}

#endif