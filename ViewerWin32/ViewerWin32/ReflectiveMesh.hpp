#pragma once


#include "Geometry.hpp"
#include "PosNormalGeometryBuffer.hpp"
#include "Transform.hpp"
#include "ReflectiveMaterial.hpp" 
#include "Camera.hpp"
#include "SceneLights.hpp"

namespace Viewer
{
	class ReflectiveMesh
	{
	private:
		Geometry& m_geometry;
		PosNormalGeometryBuffer m_geometryBuffer;

		CComPtr<ID3D11Device> m_device;

	public:
		ReflectiveMesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry);

		Transform Transform;
		ReflectiveMaterial Material;

		void Initialize();
		void Update();
		void Draw(Camera& camera);
	};;
}