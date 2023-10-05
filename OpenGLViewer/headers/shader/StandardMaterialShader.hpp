#ifndef STANDARD_MATERIAL_SHADER_HPP

#define STANDARD_MATERIAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>
#include "buffer/UniformBuffer.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"
#include "material/MaterialData.hpp"
#include "camera/Camera.hpp"

#define MAX_DIRECTIONAL_LIGHTS 3
#define MAX_POINT_LIGHTS 5

namespace Viewer
{
    class StandardMaterialShader final : public Shader
    {
    public:
        StandardMaterialShader();
        bool Initialize();

        /// @brief Sets the transform matrices.
        /// @param transformBuffer - The transform buffer
        void SetTransform(UniformBuffer<glm::mat4> &transformBuffer);

        /// @brief Sets the values of the camera.
        /// @param cameraBuffer - The buffer containing the values of the camera.
        void SetCamera(UniformBuffer<CameraData> &cameraBuffer);

        /// @brief Sets the values of the ambient light.
        /// @param ambientLightBuffer - The buffer containing the values of the ambient light.
        void SetAmbientLight(UniformBuffer<AmbientLight> &ambientLightBuffer);

        /// @brief Sets the values of the directional light.
        /// @param directionalLightsBuffer - The buffer containing the values of the directional lights.
        void SetDirectionalLights(UniformBuffer<DirectionalLight> &directionalLightsBuffer);

        /// @brief Sets the values of the point light.
        /// @param pointLightsBuffer - The buffer containing the values of the point lights.
        void SetPointLights(UniformBuffer<PointLight> &pointLightsBuffer);

        /// @brief Sets the diffuse texture.
        /// @param texture - The texture.
        void SetDiffuseTexture(Texture2D &texture);

        /// @brief Sets the specular texture.
        /// @param texture - The texture.
        void SetSpecularTexture(Texture2D &texture);

        /// @brief Sets the material.
        /// @param materialDataBuffer - The buffer containing the material data.
        void SetMaterial(UniformBuffer<MaterialData> &materialDataBuffer);

    private:
        // Material
        int m_diffuseTextureLocation;
        int m_specularTextureLocation;
    };
}

#endif