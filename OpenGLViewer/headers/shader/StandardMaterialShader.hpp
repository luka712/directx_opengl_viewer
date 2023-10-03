#ifndef STANDARD_MATERIAL_SHADER_HPP

#define STANDARD_MATERIAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>
#include "buffer/UniformBuffer.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"

#define MAX_DIRECTIONAL_LIGHTS 3
#define MAX_POINT_LIGHTS 5

namespace Viewer
{
    class StandardMaterialShader final : public Shader
    {
    public:
        StandardMaterialShader();
        bool Initialize();

        /// @brief Sets the model matrix.
        /// @param modelMatrix - The model matrix.
        void SetModelMatrix(const glm::mat4 &modelMatrix);

        /// @brief Sets the normal matrix.
        /// @param normalMatrix - The normal matrix.
        void SetNormalMatrix(const glm::mat3 &normalMatrix);

        /// @brief Sets the projection view matrix.
        /// @param projectionViewMatrix - The projection view matrix.
        void SetProjectionViewMatrix(const glm::mat4 &projectionViewMatrix);

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

        /// @brief Sets the diffuse coefficient. Diffuse coefficient tells how much of the diffuse light is reflected.
        /// @param diffuseCoefficient - The diffuse coefficient.
        void SetDiffuseCoefficient(float diffuseCoefficient);

        /// @brief Sets the specular coefficient. Specular coefficient tells how much of the specular light is reflected.
        /// @param specularCoefficient - The specular coefficient.
        void SetSpecularCoefficient(float specularCoefficient);

        /// @brief Sets the shininess. The shininess tells how much the specular light is spread.
        /// @param shininess - The shininess.
        void SetShininess(float shininess);

        /// @brief Sets the camera position.
        /// @param cameraPosition - The camera position.
        void SetCameraPosition(const glm::vec3 &cameraPosition);

    private:
        int m_modelMatrixLocation;
        int m_normalMatrixLocation;
        int m_viewProjectionMatrixLocation;

        int m_cameraPositionLocation;

        // Material
        int m_diffuseTextureLocation;
        int m_specularTextureLocation;
        int m_diffuseCoefficientLocation;
        int m_specularCoefficientLocation;
        int m_shininessLocation;
    };
}

#endif