#pragma once


#include "GeometryBuffer.hpp"
#include "Geometry.hpp"
#include "Transform.hpp"
#include "UnlitMaterial.hpp" 
#include "Camera.hpp"
#include "SceneLights.hpp"

namespace Viewer
{
	class UnlitMesh
	{
	private:
		Geometry& m_geometry;
		GeometryBuffer m_geometryBuffer;

		CComPtr<ID3D11Device> m_device;

	public:
		UnlitMesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry);

		Transform Transform;
		UnlitMaterial Material;

		void Initialize();
		void Update();
		void Draw(Camera& camera);
	};;
}