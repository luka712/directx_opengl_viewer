#pragma once

#include <DirectXMath.h>
#include "shader.hpp"
#include "AmbientLight.hpp"
#include "Texture2D.hpp"
#include "ConstantBuffer.hpp"
#include "MaterialData.hpp"
#include "Camera.hpp"

namespace Viewer
{
	struct ViewModelViewModelNormalData
	{
		DirectX::XMMATRIX ViewModelMatrix;
		DirectX::XMMATRIX ViewModelNormalMatrix;
	};

	class DebugNormalShader : public Shader
	{

	public:
		DebugNormalShader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext);

		std::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout() override;

		/// <summary>
		/// Sets the view matrix value of camera.
		/// </summary>
		void SetViewModelMatrix(ConstantBuffer<ViewModelViewModelNormalData>& cBuffer);

		/// <summary>
		/// It contains the projection  matrix.
		/// </summary>
		/// <param name="cameraBuffer"></param>
		void SetProjectionMatrix(ConstantBuffer<DirectX::XMMATRIX>&  cBuffer);


	};
}