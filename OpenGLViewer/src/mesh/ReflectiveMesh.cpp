#include "mesh/ReflectiveMesh.hpp"

namespace Viewer
{
    ReflectiveMesh::ReflectiveMesh(Geometry &geometry)
        : m_geometry(geometry)
    {
    }

    void ReflectiveMesh::Initialize()
    {
        m_geometryBuffer.Initialize(
            m_geometry.positionVertices,
            m_geometry.indices,
            m_geometry.normalVertices);

        Transform.Initialize();
        Material.Initialize();
    }

    void ReflectiveMesh::Update()
    {
        Transform.Update();
    }

    void ReflectiveMesh::Draw(Camera &camera)
    {
        Material.Use();

        Material.UpdateSelfProperties();
        Material.UpdateTransformProperties(Transform);
        Material.UpdateProperties(camera);

        m_geometryBuffer.Draw();
    }
}