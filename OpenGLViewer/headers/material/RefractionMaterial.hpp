#ifndef REFRACTION_MATERIAL_HPP

#define REFRACTION_MATERIAL_HPP

#include "shader/RefractionMaterialShader.hpp"
#include "buffer/UniformBuffer.hpp"
#include "transform/Transform.hpp"
#include "scene/SceneLights.hpp"

namespace Viewer
{
    class RefractionMaterial final 
    {
    private:
        RefractionMaterialShader *m_materialShader;
        UniformBuffer<RefractionMaterialData> m_materialBuffer;

    public:
        CubeTexture* EnvMapTexture;
        float RefractionIndex;

        RefractionMaterial();

        /// @brief Destructor.
        ~RefractionMaterial();

        void Initialize();

        void Use();

        /// @brief Updates the properties of the material. Updates own properties.
        void UpdateSelfProperties();

        /// @brief Updates the properties related to the camera.
        void UpdateProperties(Camera& camera);

        /// @brief  Updates the properties related to the transform.
        void UpdateTransformProperties(Transform& transform);
    };
}

#endif
