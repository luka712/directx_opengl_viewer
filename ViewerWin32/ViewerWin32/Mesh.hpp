#pragma once


#include "GeometryBuffer.hpp"
#include "Geometry.hpp"
#include "Transform.hpp"
#include "StandardMaterial.hpp" 
#include "Camera.hpp"
#include "SceneLights.hpp"

namespace Viewer
{
	class Mesh
	{
	private:
		Geometry& m_geometry;
		GeometryBuffer m_geometryBuffer;

		CComPtr<ID3D11Device> m_device;

	public:
		Mesh(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, Geometry& geometry);

		Transform Transform;
		StandardMaterial Material;
	
		void Initialize();
		void Update();
		void Draw(Camera& camera, SceneLights& lights);
	};;
}