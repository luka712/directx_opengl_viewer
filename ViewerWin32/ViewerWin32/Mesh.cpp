#include "Mesh.hpp"

namespace Viewer
{

	Mesh::Mesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry)
		: m_device(device), m_geometry(geometry), Transform(device, deviceContext), Material(device, deviceContext), m_geometryBuffer(device, deviceContext)
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

		Transform.Initialize();
		Material.Initialize();
	}

	void Mesh::Update()
	{
		Transform.Update();
	}

	void Mesh::Draw(Camera& camera, SceneLights& lights)
	{
		Material.Use();

		Material.UpdateSelfProperties();
		Material.UpdateTransformProperties(Transform);
		Material.UpdateCameraProperties(camera);
		Material.UpdateLightsProperties(lights);

		m_geometryBuffer.Draw();
	}

}
