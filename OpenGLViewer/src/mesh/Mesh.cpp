#include "mesh/Mesh.hpp"

namespace Viewer
{
    Mesh::Mesh(Geometry &geometry)
        : m_geometry(geometry)
    {
    }

    void Mesh::Initialize()
    {
        m_geometryBuffer.Initialize(
            m_geometry.positionVertices,
            m_geometry.indices,
            m_geometry.textureVertices,
            m_geometry.normalVertices,
            m_geometry.colorVertices);

        m_posNormalGeometryBuffer.Initialize(
            m_geometry.positionVertices,
            m_geometry.indices,
            m_geometry.normalVertices);

        Transform.Initialize();
        Material.Initialize();
        m_debugNormalMaterial.Initialize();
    }

    void Mesh::Update()
    {
        Transform.Update();
    }

    void Mesh::Draw(Camera &camera, SceneLights &lights)
    {
        Material.Use();

        Material.UpdateSelfProperties();
        Material.UpdateTransformProperties(Transform);
        Material.UpdateProperties(camera);
        Material.UpdateLightsProperties(lights);

        m_geometryBuffer.Draw();

        if (DebugNormals)
        {
            m_debugNormalMaterial.Use();

            m_debugNormalMaterial.UpdateProperties(camera, Transform);

            m_posNormalGeometryBuffer.Draw();
        }
    }
}