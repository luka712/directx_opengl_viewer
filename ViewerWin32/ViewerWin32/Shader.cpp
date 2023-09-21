#include "Shader.hpp"

namespace Viewer
{

	Shader::Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename)
		: m_vertexShaderFilename(vertexShaderFilename)
		, m_fragmentShaderFilename(fragmentShaderFilename)
	{
	}

	Shader::~Shader()
	{
		m_vertexShader.Release();
		m_pixelShader.Release();
		m_inputLayout.Release();
	}

	bool Shader::Initialize(CComPtr<ID3D11Device> device)
	{

		// Compile the vertex shader from a file
		CComPtr<ID3DBlob> vertexShaderBlob = CompileShaderFromFile(m_vertexShaderFilename, "vs_5_0");
		// Compile the pixel shader from a file
		CComPtr<ID3DBlob> pixelShaderBlob = CompileShaderFromFile(m_fragmentShaderFilename, "ps_5_0");

		if (vertexShaderBlob == nullptr)
		{
			// Handle vertex shader compilation failure
			MessageBoxW(nullptr, L"Failed to compile vertex shader", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		if (pixelShaderBlob == nullptr)
		{
			// Handle pixel shader compilation failure
			MessageBoxW(nullptr, L"Failed to compile pixel shader", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Create the vertex shader from the compiled bytecode
		HRESULT hr = device->CreateVertexShader(
			vertexShaderBlob->GetBufferPointer(),
			vertexShaderBlob->GetBufferSize(),
			nullptr,
			&m_vertexShader
		);

		if (FAILED(hr))
		{
			// Handle vertex shader creation failure
			MessageBoxW(nullptr, L"Failed to create vertex shader", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		// Create the pixel shader from the compiled bytecode
		hr = device->CreatePixelShader(
			pixelShaderBlob->GetBufferPointer(),
			pixelShaderBlob->GetBufferSize(),
			nullptr,
			&m_pixelShader
		);

		if (FAILED(hr))
		{
			// Handle pixel shader creation failure
			MessageBoxW(nullptr, L"Failed to create pixel shader", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		UINT numElements = ARRAYSIZE(layout);

		// Create the input layout
		hr = device->CreateInputLayout(
			layout,
			numElements,
			vertexShaderBlob->GetBufferPointer(),
			vertexShaderBlob->GetBufferSize(),
			&m_inputLayout
		);

		if (FAILED(hr))
		{
			// Handle input layout creation failure
			MessageBoxW(nullptr, L"Failed to create input layout", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	void Shader::Use(CComPtr<ID3D11DeviceContext> deviceContext)
	{
		deviceContext->IASetInputLayout(m_inputLayout);

		deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
		deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
	}

	// Compile a shader from a file and return the compiled bytecode
	CComPtr<ID3DBlob> Shader::CompileShaderFromFile(std::string fileName, std::string shaderModel)
	{
		// Define shader compilation flags
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS; // You can customize these flags

		CComPtr<ID3DBlob> shaderBlob = nullptr;
		CComPtr<ID3DBlob> errorBlob = nullptr;

		// Convert the file name to a wide string
		std::wstring wStr = std::wstring(fileName.begin(), fileName.end());

		// Compile the shader from the file
		HRESULT hr = D3DCompileFromFile(
			wStr.c_str(),        // Path to your HLSL file
			nullptr,             // Optional defines
			nullptr,             // Optional include files
			"main",              // Entry point function name
			shaderModel.c_str(), // Shader model (e.g., "vs_5_0" for vertex shader)
			shaderFlags,         // Compilation flags
			0,                   // Effect flags (not used for standalone shader compilation)
			&shaderBlob,         // Output compiled shader bytecode
			&errorBlob           // Output error messages (if any)
		);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				// Handle shader compilation errors by outputting error messages
				MessageBoxW(nullptr, (WCHAR*)errorBlob->GetBufferPointer(), L"Error", MB_OK | MB_ICONERROR);
			}
			return nullptr;
		}

		return shaderBlob;
	}

}