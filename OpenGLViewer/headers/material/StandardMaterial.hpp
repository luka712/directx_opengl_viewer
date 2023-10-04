#ifndef STANDARD_MATERIAL_HPP

#define STANDARD_MATERIAL_HPP

#include "shader/StandardMaterialShader.hpp"
#include "buffer/UniformBuffer.hpp"

namespace Viewer
{
    class StandardMaterial final 
    {
    private:
        StandardMaterialShader *m_materialShader;
        UniformBuffer<MaterialData> *m_materialBuffer;

    public:
        Texture2D* DiffuseTexture;
        Texture2D* SpecularTexture;

        // @brief The diffuse coefficient of the material. It is the ratio of the light that is scattered in all directions.
        float DiffuseCoefficient;
        // @brief The specular coefficient of the material. It is the ratio of the light that is reflected in a single direction.
        float SpecularCoefficient;
        // @brief The shininess of the material. It is the exponent of the specular highlight.
        float Shininess;


        StandardMaterial();

        /// @brief Destructor.
        ~StandardMaterial();

        void Initialize();

        void Use();

        /// @brief Updates the properties of the material. Updates own properties.
        void UpdateSelfProperties();

        /// @brief Updates the properties related to the camera.
        void UpdateCameraProperties(Camera& camera);

        /// @brief  Updates the properties related to the transform.
        void UpdateTranformProperties(glm::mat4x4& modelMatrix, glm::mat3x3& normalMatrix);

        /// @brief Update the properties related to the lights.
        void UpdateLightsProperties(
            UniformBuffer<AmbientLight> &ambientLightBuffer,
            UniformBuffer<DirectionalLight> &directionalLightsBuffer,
            UniformBuffer<PointLight> &pointLightsBuffer);
    };
}

#endif
