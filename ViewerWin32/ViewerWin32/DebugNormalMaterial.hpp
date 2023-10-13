#pragma once

#include "MaterialData.hpp"
#include "DebugNormalShader.hpp"
#include "Texture2D.hpp"
#include <atlbase.h>
#include "ConstantBuffer.hpp"
#include "SceneLights.hpp"
#include "Camera.hpp"
#include "Transform.hpp"

namespace Viewer
{
	class DebugNormalMaterial final
	{
	private:
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		ConstantBuffer<ViewModelViewModelNormalData> m_viewModelBuffer;

		DebugNormalShader* m_shader;


	public:
		DebugNormalMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);
		~DebugNormalMaterial();


		void Initialize();

		void Use();

		/// <summary>
		/// Updates the properties of the camera.
		/// </summary>
		void UpdateProperties(Camera& camera, Transform& transform);
	};
}
