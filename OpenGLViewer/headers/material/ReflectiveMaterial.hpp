#ifndef REFLECTIVE_MATERIAL_HPP

#define REFLECTIVE_MATERIAL_HPP

#include "shader/ReflectiveMaterialShader.hpp"
#include "buffer/UniformBuffer.hpp"
#include "transform/Transform.hpp"
#include "scene/SceneLights.hpp"
#include "texture/CubeTexture.hpp"

namespace Viewer
{
    class ReflectiveMaterial final 
    {
    private:
        ReflectiveMaterialShader *m_materialShader;

    public:
        CubeTexture* EnvMapTexture;

        ReflectiveMaterial();

        /// @brief Destructor.
        ~ReflectiveMaterial();

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
