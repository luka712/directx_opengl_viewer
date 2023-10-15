#include "ReflectiveMesh.hpp"

namespace Viewer
{

	ReflectiveMesh::ReflectiveMesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry)
		: m_device(device), m_geometry(geometry), Transform(device, deviceContext), Material(device, deviceContext), m_geometryBuffer(device, deviceContext)
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

	void ReflectiveMesh::Draw(Camera& camera)
	{
		Material.Use();

		Material.UpdateSelfProperties();
		Material.UpdateTransformProperties(Transform);
		Material.UpdateCameraProperties(camera);

		m_geometryBuffer.Draw();
	}

}
