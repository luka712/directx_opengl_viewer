#ifndef REFLECTIVE_MATERIAL_SHADER_HPP

#define REFLECTIVE_MATERIAL_SHADER_HPP

#include "shader/Shader.hpp"
#include <glm/glm.hpp>
#include "buffer/UniformBuffer.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"
#include "material/MaterialData.hpp"
#include "camera/Camera.hpp"
#include "texture/CubeTexture.hpp"


namespace Viewer
{
    class ReflectiveMaterialShader final : public Shader
    {
    public:
        ReflectiveMaterialShader();
        bool Initialize();

        /// @brief Sets the transform matrices.
        /// @param transformBuffer - The transform buffer
        void SetTransform(UniformBuffer<glm::mat4> &transformBuffer);

        /// @brief Sets the values of the camera.
        /// @param cameraBuffer - The buffer containing the values of the camera.
        void SetCamera(UniformBuffer<CameraData> &cameraBuffer);

        /// @brief Sets the diffuse texture.
        /// @param texture - The texture.
        void SetEnvMapTexture(CubeTexture& texture);


    private:
        // Material
        int m_cubeTextureLocation;
    };
}

#endif