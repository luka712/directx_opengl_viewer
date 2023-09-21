#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <atlbase.h> // Contains the declaration of CComPtr.


namespace Viewer
{
	class Shader
	{
	private:
		std::string m_vertexShaderFilename;
		std::string m_fragmentShaderFilename;

		CComPtr<ID3D11VertexShader> m_vertexShader;
		CComPtr<ID3D11PixelShader> m_pixelShader;
		CComPtr<ID3D11InputLayout> m_inputLayout;

		/// <summary>
		/// Compiles a shader from a file.
		/// </summary>
		/// <param name="fileName">The filename.</param>
		/// <param name="shaderModel">Shader model, for D3D11 it is vs_5_0, ps_5_0, gs_5_0, hs_5_0, ds_5_0, cs_5_0</param>
		/// <returns></returns>
		CComPtr<ID3DBlob> CompileShaderFromFile(std::string fileName, std::string shaderModel);

	public:
		Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename);
		~Shader();

		bool Initialize(CComPtr<ID3D11Device> device);
		void Use(CComPtr<ID3D11DeviceContext> deviceContext);

	};
}