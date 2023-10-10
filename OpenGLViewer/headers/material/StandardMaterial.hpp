#ifndef STANDARD_MATERIAL_HPP

#define STANDARD_MATERIAL_HPP

#include "shader/StandardMaterialShader.hpp"
#include "buffer/UniformBuffer.hpp"
#include "transform/Transform.hpp"
#include "scene/SceneLights.hpp"

namespace Viewer
{
    class StandardMaterial final 
    {
    private:
        StandardMaterialShader *m_materialShader;
        UniformBuffer<PhongMaterialData> *m_materialBuffer;
        UniformBuffer<glm::vec2> *m_textureTillingBuffer;

    public:
        Texture2D* DiffuseTexture;
        Texture2D* SpecularTexture;

        /// @brief The tilling of the texture. Usually 1,1. Larger values will repeat the texture.
        glm::vec2 TextureTilling;

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
        void UpdateTransformProperties(Transform& transform);

        /// @brief Update the properties related to the lights.
        void UpdateLightsProperties(SceneLights& lights);
    };
}

#endif
