#include "skybox/Skybox.hpp"
#include "geometry/Geometry.hpp"

namespace Viewer
{
    void Skybox::Initialize()
    {
        Geometry geometry = Geometry::CreateSkyboxGeometry();
        m_geometryBuffer.Initialize(
            geometry.positionVertices,
            geometry.indices,
            geometry.textureVertices,
            geometry.normalVertices,
            geometry.colorVertices);

        m_shader.Initialize();
    }

    void Skybox::Draw(Camera& camera)
    {
        glDepthMask(GL_FALSE);
        m_shader.Use();
        m_shader.SetTexture(*SkyTexture);
        m_shader.SetCamera(camera.GetSkyboxCameraBuffer());
        m_geometryBuffer.Draw();
        glDepthMask(GL_TRUE);
    }

}