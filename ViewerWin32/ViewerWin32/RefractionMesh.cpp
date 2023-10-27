#include "RefractionMesh.hpp"

namespace Viewer
{

	RefractionMesh::RefractionMesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry)
		: m_device(device), m_geometry(geometry), Transform(device, deviceContext), Material(device, deviceContext), m_geometryBuffer(device, deviceContext)
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

	void RefractionMesh::Draw(Camera& camera)
	{
		Material.Use();

		Material.UpdateSelfProperties();
		Material.UpdateTransformProperties(Transform);
		Material.UpdateCameraProperties(camera);

		m_geometryBuffer.Draw();
	}

}
