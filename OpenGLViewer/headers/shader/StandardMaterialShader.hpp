#ifndef STANDARD_MATERIAL_SHADER_HPP

#define STANDARD_MATERIAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>

namespace Viewer
{
    class StandardMaterialShader final : public Shader
    {
    public:
        StandardMaterialShader();
        bool Initialize();

        void SetModelMatrix(const glm::mat4& modelMatrix);
        void SetProjectionViewMatrix(const glm::mat4& projectionViewMatrix);

    private:
        int m_modelMatrixLocation;
        int m_viewProjectionMatrixLocation;
    };
}

#endif