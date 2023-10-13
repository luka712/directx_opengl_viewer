#ifndef DEBUG_NORMAL_MATERIAL_HPP

#define DEBUG_NORMAL_MATERIAL_HPP

#include "shader/DebugNormalShader.hpp"
#include "buffer/UniformBuffer.hpp"
#include "transform/Transform.hpp"
#include "scene/SceneLights.hpp"

namespace Viewer
{
    class DebugNormalMaterial final 
    {
    private:
        DebugNormalShader *m_shader;

        UniformBuffer<ViewModelViewModelNormalData> m_viewModelBuffer;

    public:

        DebugNormalMaterial();

        /// @brief Destructor.
        ~DebugNormalMaterial();

        void Initialize();

        void Use();

        /// @brief Updates the properties related to the camera.
        void UpdateProperties(Camera& camera, Transform& transform);
    };
}

#endif
