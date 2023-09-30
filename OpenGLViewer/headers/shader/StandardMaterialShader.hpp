#ifndef STANDARD_MATERIAL_SHADER_HPP

#define STANDARD_MATERIAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>

#define MAX_DIRECTIONAL_LIGHTS 3

namespace Viewer
{
    class StandardMaterialShader final : public Shader
    {
    public:
        StandardMaterialShader();
        bool Initialize();

        void SetModelMatrix(const glm::mat4 &modelMatrix);
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

    private:
        int m_modelMatrixLocation;
        int m_viewProjectionMatrixLocation;

        // Ambient light
        int m_ambientLightIntensityLocation;
        int m_ambientLightColorLocation;

        // Directional lights
        int m_directionalLightDirectionLocation[MAX_DIRECTIONAL_LIGHTS];
        int m_directionalLightIntensityLocation[MAX_DIRECTIONAL_LIGHTS];
        int m_directionalLightColorLocation[MAX_DIRECTIONAL_LIGHTS];
    };
}

#endif