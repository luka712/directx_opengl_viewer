#pragma once


#include "Geometry.hpp"
#include "PosNormalGeometryBuffer.hpp"
#include "Transform.hpp"
#include "RefractionMaterial.hpp" 
#include "Camera.hpp"
#include "SceneLights.hpp"

namespace Viewer
{
	class RefractionMesh
	{
	private:
		Geometry& m_geometry;
		PosNormalGeometryBuffer m_geometryBuffer;

		CComPtr<ID3D11Device> m_device;

	public:
		RefractionMesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry);

		Transform Transform;
		RefractionMaterial Material;

		void Initialize();
		void Update();
		void Draw(Camera& camera);
	};;
}