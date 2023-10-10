#ifndef UNLIT_MATERIAL_SHADER_HPP

#define UNLIT_MATERIAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>
#include "buffer/UniformBuffer.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"
#include "material/MaterialData.hpp"
#include "camera/Camera.hpp"

namespace Viewer
{
    class UnlitMaterialShader final : public Shader
    {
    public:
        UnlitMaterialShader();
        bool Initialize();

        /// @brief Sets the transform matrices.
        /// @param transformBuffer - The transform buffer
        void SetTransform(UniformBuffer<glm::mat4> &transformBuffer);

        /// @brief Sets the values of the camera.
        /// @param cameraBuffer - The buffer containing the values of the camera.
        void SetCamera(UniformBuffer<CameraData> &cameraBuffer);

        /// @brief Sets the texture tilling.
        /// @param textureTillingBuffer The buffer containing the texture tilling.
        void SetTextureTilling(UniformBuffer<glm::vec2> &textureTillingBuffer);

        /// @brief Sets the diffuse texture.
        /// @param texture - The texture.
        void SetDiffuseTexture(Texture2D &texture);

        /// @brief Sets the material.
        /// @param materialDataBuffer - The buffer containing the material data.
        void SetMaterial(UniformBuffer<UnlitMaterialData> &materialDataBuffer);

    private:
        // Material
        int m_diffuseTextureLocation;
    };
}

#endif