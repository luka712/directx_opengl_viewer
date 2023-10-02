// HelloTriangleD3D11.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ViewerWin32.h"
#include <windows.h>
#include <combaseapi.h>
#include <d3d11.h>
#include <string>
#include "Renderer.hpp"
#include "StandardMaterialShader.hpp"
#include "GeometryBuffer.hpp"
#include "Geometry.hpp"
#include "ConstantBuffer.hpp"
#include "MatrixUtil.hpp"
#include "Texture2D.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Material.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Viewer::Material material = { 0.5f, 3.0f, 12.0f };

Viewer::AmbientLight ambientLight = { 0.3f, DirectX::XMFLOAT3(1, 1, 1) };
Viewer::DirectionalLight directionalLights[3] = {
	{ DirectX::XMFLOAT3(1, -1, 0), 1.0f, DirectX::XMFLOAT3(1,1,1) },
	{ DirectX::XMFLOAT3(-1, 0, 0), 0.5f, DirectX::XMFLOAT3(1,1,1) },
	{ DirectX::XMFLOAT3(1, 0, 0), 0.5f, DirectX::XMFLOAT3(1,1,1) }
};
Viewer::PointLight pointLights[5] = {
	{ DirectX::XMFLOAT3(1, 0, 0), 0.0f, DirectX::XMFLOAT3(1,0,0) },
	{ DirectX::XMFLOAT3(0, 1, 0), 0.0f, DirectX::XMFLOAT3(0,1,0) },
	{ DirectX::XMFLOAT3(0, 0, 1), 0.0f, DirectX::XMFLOAT3(0,0,1) },
	{ DirectX::XMFLOAT3(1, 1, 0), 0.0f, DirectX::XMFLOAT3(1,1,0) },
	{ DirectX::XMFLOAT3(0, 1, 1), 0.0f, DirectX::XMFLOAT3(0,1,1) }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	unsigned int width = 1280;
	unsigned int height = 720;

	// Initialize COM
	HRESULT hr = CoInitialize(nullptr);
	if (FAILED(hr))
	{
		MessageBoxW(nullptr, L"Failed to initialize COM", L"Error", MB_OK | MB_ICONERROR);
		return hr;
	}

	const wchar_t CLASS_NAME[] = L"MainWindow";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND windowHandle = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Obj Viewer",					// Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (windowHandle == NULL)
	{
		DWORD error = GetLastError();
		std::wstring errorString = std::wstring(L"Failed to create window. Error: ") + std::to_wstring(error);
		MessageBoxW(nullptr, errorString.c_str(), L"Error", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	ShowWindow(windowHandle, nCmdShow);


	Viewer::Renderer renderer;
	bool rendererInitialized = renderer.Initialize(windowHandle, width, height);
	if (!rendererInitialized)
	{
		return FALSE;
	}

	Viewer::StandardMaterialShader shader;
	shader.Initialize(renderer.GetDevice());

	Viewer::Geometry geometry = Viewer::Geometry::CreateCubeGeometry();
	Viewer::GeometryBuffer geometryBuffer;
	geometryBuffer.Initialize(renderer.GetDevice(),
		geometry.positionVertices,
		geometry.indices,
		geometry.textureVertices,
		geometry.normalVertices,
		geometry.colorVertices);

	Viewer::ConstantBuffer<DirectX::XMMATRIX> projectionViewBuffer;
	projectionViewBuffer.Initialize(renderer.GetDevice());

	Viewer::ConstantBuffer<DirectX::XMMATRIX> modelBuffer;
	modelBuffer.Initialize(renderer.GetDevice());

	Viewer::ConstantBuffer<DirectX::XMMATRIX> normalMatrixBuffer;
	normalMatrixBuffer.Initialize(renderer.GetDevice());

	Viewer::ConstantBuffer<Viewer::Material> materialBuffer;
	materialBuffer.Initialize(renderer.GetDevice());

	Viewer::ConstantBuffer<Viewer::AmbientLight> ambientLightBuffer;
	ambientLightBuffer.Initialize(renderer.GetDevice());

	Viewer::ConstantBuffer<Viewer::DirectionalLight> directionalLightBuffer;
	directionalLightBuffer.Initialize(renderer.GetDevice(), 3);

	Viewer::ConstantBuffer<Viewer::PointLight> pointLightBuffer;
	pointLightBuffer.Initialize(renderer.GetDevice(), 5);

	Viewer::ConstantBuffer<DirectX::XMVECTOR> eyePositionBuffer;
	eyePositionBuffer.Initialize(renderer.GetDevice());


	MSG msg;

	// DirectX::XMMATRIX projectionViewMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterRH(-10, 10, -5, 5, 1, -1));
	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(3, 3, -3, 0);
	DirectX::XMVECTOR focusPoint = DirectX::XMVectorSet(0, 0, 0, 0);
	DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(0, 1, 0, 0);


	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtRH(eyePosition, focusPoint, upDirection);

	float aspectRatio = (float)width / (float)height;
	DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovRH(DirectX::XM_PI / 4.0, aspectRatio, 0.1, 1000);

	DirectX::XMMATRIX projectionViewMatrix = DirectX::XMMatrixTranspose(viewMatrix * projectionMatrix);
	DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0, 0, 0));
	DirectX::XMMATRIX normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, modelMatrix));

	Viewer::MatrixUtil::Print(modelMatrix);

	Viewer::Texture2D diffuseTexture;
	diffuseTexture.Initialize(renderer.GetDevice(), "crate_texture.png");

	Viewer::Texture2D specularTexture;
	specularTexture.Initialize(renderer.GetDevice(), "crate_specular.png");

	// Main message loop:
	while (true)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		projectionViewBuffer.Update(renderer.GetDeviceContext(), projectionViewMatrix);
		modelBuffer.Update(renderer.GetDeviceContext(), modelMatrix);
		normalMatrixBuffer.Update(renderer.GetDeviceContext(), normalMatrix);
		materialBuffer.Update(renderer.GetDeviceContext(), material);
		ambientLightBuffer.Update(renderer.GetDeviceContext(), ambientLight);
		directionalLightBuffer.Update(renderer.GetDeviceContext(), directionalLights, 3);
		pointLightBuffer.Update(renderer.GetDeviceContext(), pointLights, 5);
		eyePositionBuffer.Update(renderer.GetDeviceContext(), eyePosition);

		renderer.Begin();

		// DRAW
		shader.Use(renderer.GetDeviceContext());

		shader.SetProjectionViewMatrix(renderer.GetDeviceContext(), projectionViewBuffer.GetBuffer());
		shader.SetModelMatrix(renderer.GetDeviceContext(), modelBuffer.GetBuffer());
		shader.SetNormalMatrix(renderer.GetDeviceContext(), normalMatrixBuffer.GetBuffer());

		// material
		shader.SetMaterial(renderer.GetDeviceContext(), materialBuffer.GetBuffer());

		// lights
		shader.SetAmbientLight(renderer.GetDeviceContext(), ambientLightBuffer.GetBuffer());
		shader.SetDirectionalLights(renderer.GetDeviceContext(), directionalLightBuffer.GetBuffer());
		shader.SetPointLights(renderer.GetDeviceContext(), pointLightBuffer.GetBuffer());

		// Pass texture to shader
		shader.SetDiffuseTexture(renderer.GetDeviceContext(), diffuseTexture);
		shader.SetSpecularTexture(renderer.GetDeviceContext(), specularTexture);

		shader.SetEyePosition(renderer.GetDeviceContext(), eyePositionBuffer.GetBuffer());

		geometryBuffer.Draw(renderer.GetDeviceContext());

		// PRESENT
		renderer.End();

		// delay 16ms to simulate 60fps and avoid 100% CPU usage
		Sleep(16);
	}

	// Uninitialize COM when done
	CoUninitialize();

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}