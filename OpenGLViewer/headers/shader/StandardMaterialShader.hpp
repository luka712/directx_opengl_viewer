#ifndef STANDARD_MATERIAL_SHADER_HPP

#define STANDARD_MATERIAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>

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
        /// @param intensity - The intensity of the light.
        /// @param color - The color of the light.
        void SetAmbientLight(float intensity, const glm::vec3 &color);

        /// @brief Sets the values of the directional light.
        /// @param index - The index of the light.
        /// @param direction - The direction of the light.
        /// @param intensity - The intensity of the light.
        /// @param color - The color of the light.
        void SetDirectionalLight(size_t index, const glm::vec3 &direction, float intensity, const glm::vec3 &color);

        /// @brief Sets the values of the point light.
        /// @param index - The index of the light.
        /// @param position - The position of the light.
        /// @param intensity - The intensity of the light.
        /// @param color - The color of the light.
        void SetPointLight(size_t index, const glm::vec3 &position, float intensity, const glm::vec3 &color);

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


        // Ambient light
        int m_ambientLightIntensityLocation;
        int m_ambientLightColorLocation;

        // Directional lights
        int m_directionalLightDirectionLocation[MAX_DIRECTIONAL_LIGHTS];
        int m_directionalLightIntensityLocation[MAX_DIRECTIONAL_LIGHTS];
        int m_directionalLightColorLocation[MAX_DIRECTIONAL_LIGHTS];
        
        // Point lights
        int m_pointLightPositionLocation[MAX_POINT_LIGHTS];
        int m_pointLightIntensityLocation[MAX_POINT_LIGHTS];
        int m_pointLightColorLocation[MAX_POINT_LIGHTS];
    };
}

#endif