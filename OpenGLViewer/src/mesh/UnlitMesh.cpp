#include "mesh/UnlitMesh.hpp"

namespace Viewer
{
    UnlitMesh::UnlitMesh(Geometry &geometry)
        : m_geometry(geometry)
    {
    }

    void UnlitMesh::Initialize()
    {
        m_geometryBuffer.Initialize(
            m_geometry.positionVertices,
            m_geometry.indices,
            m_geometry.textureVertices,
            m_geometry.normalVertices,
            m_geometry.colorVertices);

        Transform.Initialize();
        Material.Initialize();
    }

    void UnlitMesh::Update()
    {
        Transform.Update();
    }

    void UnlitMesh::Draw(Camera &camera)
    {
        Material.Use();

        Material.UpdateSelfProperties();
        Material.UpdateTransformProperties(Transform);
        Material.UpdateProperties(camera);

        m_geometryBuffer.Draw();
    }
}