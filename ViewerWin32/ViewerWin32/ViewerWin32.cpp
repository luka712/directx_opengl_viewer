// HelloTriangleD3D11.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ViewerWin32.h"
#include <windows.h>
#include <Windowsx.h>
#include <Winuser.h>
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
#include "MaterialData.hpp"
#include "ImageLoader.hpp"
#include "StandardMaterial.hpp"
#include "Camera.hpp"
#include "OrbitCamera.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Viewer::MouseState g_mouseState;

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

	unsigned int Width = 1280;
	unsigned int Height = 720;

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
		CW_USEDEFAULT, CW_USEDEFAULT, Width, Height,

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
	bool rendererInitialized = renderer.Initialize(windowHandle, Width, Height);
	if (!rendererInitialized)
	{
		return FALSE;
	}

	Viewer::ImageLoader imageLoader;
	Viewer::ImageData* imageData = imageLoader.Load("crate_texture.png");
	Viewer::Texture2D diffuseTexture(renderer.GetDevice());
	diffuseTexture.Initialize(imageData->Data, imageData->Width, imageData->Height);
	delete imageData;

	Viewer::ImageData* imageData2 = imageLoader.Load("crate_specular.png");
	Viewer::Texture2D specularTexture(renderer.GetDevice());
	specularTexture.Initialize(imageData2->Data, imageData2->Width, imageData2->Height);
	delete imageData2;

	Viewer::StandardMaterial material(renderer.GetDevice(), renderer.GetDeviceContext());
	material.Initialize();
	material.DiffuseTexture = &diffuseTexture;
	material.SpecularTexture = &specularTexture;
	material.DiffuseCoefficient = 0.5f;
	material.SpecularCoefficient = 3.0f;
	material.Shininess = 12.0f;

	Viewer::Geometry geometry = Viewer::Geometry::CreateCubeGeometry();
	Viewer::GeometryBuffer geometryBuffer;
	geometryBuffer.Initialize(renderer.GetDevice(),
		geometry.positionVertices,
		geometry.indices,
		geometry.textureVertices,
		geometry.normalVertices,
		geometry.colorVertices);


	Viewer::ConstantBuffer<DirectX::XMMATRIX> modelBuffer(renderer.GetDevice(), renderer.GetDeviceContext());
	modelBuffer.Initialize();

	Viewer::ConstantBuffer<DirectX::XMMATRIX> normalMatrixBuffer(renderer.GetDevice(), renderer.GetDeviceContext());
	normalMatrixBuffer.Initialize();



	Viewer::ConstantBuffer<Viewer::AmbientLight> ambientLightBuffer(renderer.GetDevice(), renderer.GetDeviceContext());
	ambientLightBuffer.Initialize();

	Viewer::ConstantBuffer<Viewer::DirectionalLight> directionalLightBuffer(renderer.GetDevice(), renderer.GetDeviceContext());
	directionalLightBuffer.Initialize(3);

	Viewer::ConstantBuffer<Viewer::PointLight> pointLightBuffer(renderer.GetDevice(), renderer.GetDeviceContext());
	pointLightBuffer.Initialize(5);


	MSG msg;

	DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0, 0, 0));
	DirectX::XMMATRIX normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, modelMatrix));

	Viewer::MatrixUtil::Print(modelMatrix);



	float aspectRatio = (float)Width / (float)Height;
	Viewer::OrbitCamera camera(renderer.GetDevice(), renderer.GetDeviceContext(), aspectRatio);
	camera.Initialize();


	// Main message loop:
	while (true)
	{
		g_mouseState.ResetDeltas();
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		camera.Update(g_mouseState);


		modelBuffer.Update(modelMatrix);
		normalMatrixBuffer.Update(normalMatrix);
		ambientLightBuffer.Update(ambientLight);
		directionalLightBuffer.Update(directionalLights, 3);
		pointLightBuffer.Update(pointLights, 5);

		renderer.Begin();

		// DRAW
		material.Use();

		material.UpdateSelfProperties();
		material.UpdateCameraProperties(camera);
		material.UpdateTransformProperties(modelBuffer, normalMatrixBuffer);
		material.UpdateLightsProperties(ambientLightBuffer, directionalLightBuffer, pointLightBuffer);

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

	// wheel scroll
	case WM_MOUSEWHEEL:
		g_mouseState.DeltaWheelY = GET_WHEEL_DELTA_WPARAM(wParam);
		return 0;		

	// Left button down/up
	case WM_LBUTTONDOWN :
		g_mouseState.LeftButton = true;
		return 0;
	case WM_LBUTTONUP:
		g_mouseState.LeftButton = false;
		return 0;

	// Mouse move
	case WM_MOUSEMOVE:
		
		g_mouseState.X = GET_X_LPARAM(lParam);
		g_mouseState.Y = GET_Y_LPARAM(lParam);
		g_mouseState.DeltaX = g_mouseState.X - g_mouseState.LastX;
		g_mouseState.DeltaY = g_mouseState.Y - g_mouseState.LastY;
		g_mouseState.LastX = g_mouseState.X;
		g_mouseState.LastY = g_mouseState.Y;
		return 0;

	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;


	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}