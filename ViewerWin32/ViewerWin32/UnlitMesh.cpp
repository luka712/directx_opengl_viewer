#include "UnlitMesh.hpp"

namespace Viewer
{

	UnlitMesh::UnlitMesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry)
		: m_device(device), m_geometry(geometry), Transform(device, deviceContext), Material(device, deviceContext), m_geometryBuffer(device, deviceContext)
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

	void UnlitMesh::Draw(Camera& camera)
	{
		Material.Use();

		Material.UpdateSelfProperties();
		Material.UpdateTransformProperties(Transform);
		Material.UpdateCameraProperties(camera);

		m_geometryBuffer.Draw();
	}

}
