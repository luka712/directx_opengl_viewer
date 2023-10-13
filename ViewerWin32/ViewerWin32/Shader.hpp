#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <atlbase.h> // Contains the declaration of CComPtr.
#include <vector>

namespace Viewer
{

	class Shader
	{
	protected:
		int m_layout;
		CComPtr<ID3D11Device> m_device;
		CComPtr<ID3D11DeviceContext> m_deviceContext;

		std::string m_vertexShaderFilename;
		std::string m_fragmentShaderFilename;
		std::string m_geometryShaderFilename;

		CComPtr<ID3D11VertexShader> m_vertexShader;
		CComPtr<ID3D11PixelShader> m_pixelShader;
		CComPtr<ID3D11GeometryShader> m_geometryShader;

		CComPtr<ID3D11InputLayout> m_inputLayout;

		/// <summary>
		/// Compiles a shader from a file.
		/// </summary>
		/// <param name="fileName">The filename.</param>
		/// <param name="shaderModel">Shader model, for D3D11 it is vs_5_0, ps_5_0, gs_5_0, hs_5_0, ds_5_0, cs_5_0</param>
		/// <returns></returns>
		CComPtr<ID3DBlob> CompileShaderFromFile(std::string fileName, std::string shaderModel);

	public:
		Shader(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext,
			std::string vertexShaderFilename, std::string fragmentShaderFilename, std::string geometryShaderFilename = "");
		~Shader();

		/// <summary>
		/// Gets the input layout.
		/// By default
		///  position: float3
		///  texcoord: float2
		///  normal: float3
		///  color: float3
		/// </summary>
		/// <returns></returns>
		virtual std::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

		bool Initialize();
		void Use();

	};
}