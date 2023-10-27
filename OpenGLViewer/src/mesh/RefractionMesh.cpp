#include "mesh/RefractionMesh.hpp"

namespace Viewer
{
    RefractionMesh::RefractionMesh(Geometry &geometry)
        : m_geometry(geometry)
    {
    }

    void RefractionMesh::Initialize()
    {
        m_geometryBuffer.Initialize(
            m_geometry.positionVertices,
            m_geometry.indices,
            m_geometry.normalVertices);

        Transform.Initialize();
        Material.Initialize();
    }

    void RefractionMesh::Update()
    {
        Transform.Update();
    }

    void RefractionMesh::Draw(Camera &camera)
    {
        Material.Use();

        Material.UpdateSelfProperties();
        Material.UpdateTransformProperties(Transform);
        Material.UpdateProperties(camera);

        m_geometryBuffer.Draw();
    }
}