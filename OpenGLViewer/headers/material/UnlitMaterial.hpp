#ifndef UNLIT_MATERIAL_HPP

#define UNLIT_MATERIAL_HPP

#include "shader/UnlitMaterialShader.hpp"
#include "buffer/UniformBuffer.hpp"
#include "transform/Transform.hpp"
#include "scene/SceneLights.hpp"

namespace Viewer
{
    class UnlitMaterial final 
    {
    private:
        UnlitMaterialShader *m_materialShader;
        UniformBuffer<UnlitMaterialData> *m_materialBuffer;
        UniformBuffer<glm::vec2> *m_textureTillingBuffer;

    public:
        Texture2D* DiffuseTexture;

        /// @brief The diffuse color of the material.
        glm::vec3 DiffuseColor;

        /// @brief The intensity of the material.
        float Intensity;

        /// @brief The tilling of the texture. Usually 1,1. Larger values will repeat the texture.
        glm::vec2 TextureTilling;

        UnlitMaterial();

        /// @brief Destructor.
        ~UnlitMaterial();

        void Initialize();

        void Use();

        /// @brief Updates the properties of the material. Updates own properties.
        void UpdateSelfProperties();

        /// @brief Updates the properties related to the camera.
        void UpdateCameraProperties(Camera& camera);

        /// @brief  Updates the properties related to the transform.
        void UpdateTransformProperties(Transform& transform);
    };
}

#endif
