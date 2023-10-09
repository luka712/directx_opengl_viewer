#ifndef SKYBOX_HPP

#define SKYBOX_HPP

#include "buffer/GeometryBuffer.hpp"
#include "shader/SkyboxShader.hpp"

namespace Viewer 
{
    class Skybox
    {
    private:
        GeometryBuffer m_geometryBuffer;
        SkyboxShader m_shader;

    public:
        CubeTexture* SkyTexture;
        Skybox() = default;

        void Initialize();
        void Draw(Camera &camera);
    };
}

#endif 