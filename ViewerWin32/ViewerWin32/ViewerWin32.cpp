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
#include "MaterialData.hpp"
#include "ImageLoader.hpp"
#include "StandardMaterial.hpp"
#include "Camera.hpp"
#include "OrbitCamera.hpp"
#include "SceneLights.hpp"
#include "Transform.hpp"
#include "TextureLoader.hpp"
#include "Mesh.hpp"
#include "CubeTexture.hpp"
#include "Skybox.hpp"
#include "UnlitMesh.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Viewer::MouseState g_mouseState;


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

	Viewer::TextureLoader texLoader(renderer.GetDevice());

	Viewer::Geometry cubeGeometry = Viewer::Geometry::CreateCubeGeometry();
	Viewer::Mesh cubeMesh(renderer.GetDevice(), renderer.GetDeviceContext(), cubeGeometry);
	cubeMesh.Initialize();
	cubeMesh.Material.DiffuseTexture = texLoader.LoadFromImg("crate_texture.png");
	cubeMesh.Material.SpecularTexture = texLoader.LoadFromImg("crate_specular.png");
	cubeMesh.Material.DiffuseCoefficient = 0.5f;
	cubeMesh.Material.SpecularCoefficient = 3.0f;
	cubeMesh.Material.Shininess = 12.0f;


	Viewer::Geometry floorGeometry = Viewer::Geometry::CreateQuadGeometry();
	Viewer::Mesh floorMesh(renderer.GetDevice(), renderer.GetDeviceContext(), floorGeometry);
	floorMesh.Initialize();
	floorMesh.Material.DiffuseTexture = texLoader.LoadFromImg("wood_diffuse.png");
	floorMesh.Material.SpecularTexture = texLoader.LoadFromImg("wood_specular.png");
	floorMesh.Material.DiffuseCoefficient = 0.5f;
	floorMesh.Material.SpecularCoefficient = 3.0f;
	floorMesh.Material.Shininess = 24.0f;
	floorMesh.Material.TextureTilling = DirectX::XMFLOAT2(5.0f, 5.0f);
	floorMesh.Transform.Position.y = -0.5;
	floorMesh.Transform.Scale.x = 10;
	floorMesh.Transform.Scale.y = 10;
	floorMesh.Transform.Rotation.x = 90;


	Viewer::UnlitMesh unlitMesh[5] =
	{
		Viewer::UnlitMesh(renderer.GetDevice(), renderer.GetDeviceContext(),cubeGeometry),
		Viewer::UnlitMesh(renderer.GetDevice(), renderer.GetDeviceContext(),cubeGeometry),
		Viewer::UnlitMesh(renderer.GetDevice(), renderer.GetDeviceContext(),cubeGeometry),
		Viewer::UnlitMesh(renderer.GetDevice(), renderer.GetDeviceContext(),cubeGeometry),
		Viewer::UnlitMesh(renderer.GetDevice(), renderer.GetDeviceContext(),cubeGeometry),
	};
	for (int i = 0; i < 5; i++)
	{
		unlitMesh[i].Initialize();
	}

	Viewer::Skybox skybox(renderer.GetDevice(), renderer.GetDeviceContext(), renderer);
	skybox.SkyTexture = texLoader.LoadFromImg("right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg");
	skybox.Initialize();

	Viewer::SceneLights sceneLights(renderer.GetDevice(), renderer.GetDeviceContext());
	sceneLights.Initialize();

	MSG msg;


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

		sceneLights.Update();
		camera.Update(g_mouseState);
		floorMesh.Update();
		cubeMesh.Update();
		for (int i = 0; i < 5; i++)
		{
			unlitMesh[i].Transform.Position = sceneLights.GetPointLights(i).Position;
			unlitMesh[i].Transform.Scale = DirectX::XMFLOAT3(0.2f, 0.2f, 0.2f);
			unlitMesh[i].Material.DiffuseColor = sceneLights.GetPointLights(i).Color;
			unlitMesh[i].Material.Intensity = sceneLights.GetPointLights(i).Intensity;
			unlitMesh[i].Update();
		}

		renderer.Begin();

		// DRAW
		skybox.Draw(camera);
		cubeMesh.Draw(camera, sceneLights);
		floorMesh.Draw(camera, sceneLights);
		for (int i = 0; i < 5; i++)
		{
			unlitMesh[i].Draw(camera);
		}

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
	case WM_LBUTTONDOWN:
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