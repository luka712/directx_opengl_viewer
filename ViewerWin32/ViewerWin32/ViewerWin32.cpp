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
#include "ReflectiveMesh.hpp"
#include "RefractionMesh.hpp"
#include "RenderTarget.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Viewer::MouseState g_mouseState;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	unsigned int Width = 1920;
	unsigned int Height = 1080;

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

	Viewer::RenderTarget renderTarget(renderer.GetDevice(), renderer.GetDeviceContext(), renderer, Width, Height);
	renderTarget.Initialize();

	Viewer::TextureLoader texLoader(renderer.GetDevice());
	Viewer::CubeTexture* skyboxTexture = texLoader.LoadFromImg("right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg");

	Viewer::Geometry cubeGeometry = Viewer::Geometry::CreateCubeGeometry();
	Viewer::Mesh cubeMesh(renderer.GetDevice(), renderer.GetDeviceContext(), cubeGeometry);
	cubeMesh.DebugNormals = true;
	cubeMesh.Initialize();
	cubeMesh.Material.DiffuseTexture = texLoader.LoadFromImg("crate_texture.png");
	cubeMesh.Material.SpecularTexture = texLoader.LoadFromImg("crate_specular.png");
	cubeMesh.Material.DiffuseCoefficient = 0.5f;
	cubeMesh.Material.SpecularCoefficient = 3.0f;
	cubeMesh.Material.Shininess = 32.0f;


	Viewer::Geometry quadGeometry = Viewer::Geometry::CreateQuadGeometry();
	Viewer::Mesh floorMesh(renderer.GetDevice(), renderer.GetDeviceContext(), quadGeometry);
	floorMesh.DebugNormals = true;
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

	Viewer::Mesh mirrorMesh(renderer.GetDevice(), renderer.GetDeviceContext(), quadGeometry);
	mirrorMesh.Initialize();
	mirrorMesh.DebugNormals = true;
	mirrorMesh.Transform.Position = DirectX::XMFLOAT3(0, 2, 5);
	mirrorMesh.Transform.Scale = DirectX::XMFLOAT3(5, 5, 1);
	mirrorMesh.Material.DiffuseTexture = &renderTarget.GetTexture();
	mirrorMesh.Material.SpecularTexture = &renderTarget.GetTexture();

	Viewer::ReflectiveMesh reflectiveCubeMesh(renderer.GetDevice(), renderer.GetDeviceContext(), cubeGeometry);
	reflectiveCubeMesh.Initialize();
	reflectiveCubeMesh.Material.EnvMapTexture = skyboxTexture;
	reflectiveCubeMesh.Transform.Position.x = 3.0f;

	Viewer::RefractionMesh refractionCubeMesh(renderer.GetDevice(), renderer.GetDeviceContext(), cubeGeometry);
	refractionCubeMesh.Initialize();
	refractionCubeMesh.Material.RefractionIndex = 1.0f;
	refractionCubeMesh.Material.EnvMapTexture = skyboxTexture;
	refractionCubeMesh.Transform.Position.x = -3.0f;


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
	skybox.SkyTexture = skyboxTexture;
	skybox.Initialize();

	Viewer::SceneLights sceneLights(renderer.GetDevice(), renderer.GetDeviceContext());
	sceneLights.Initialize();

	MSG msg;


	float aspectRatio = (float)Width / (float)Height;
	Viewer::OrbitCamera camera(renderer.GetDevice(), renderer.GetDeviceContext(), aspectRatio);
	camera.Initialize();

	Viewer::Camera textureCamera(renderer.GetDevice(), renderer.GetDeviceContext(), 1);
	textureCamera.EyePosition.m128_f32[0] = mirrorMesh.Transform.Position.x;
	textureCamera.EyePosition.m128_f32[1] = mirrorMesh.Transform.Position.y;
	textureCamera.EyePosition.m128_f32[2] = 6;
	textureCamera.LookAtPosition.m128_f32[0] = mirrorMesh.Transform.Position.x;
	textureCamera.LookAtPosition.m128_f32[1] = mirrorMesh.Transform.Position.y;
	textureCamera.LookAtPosition.m128_f32[2] = mirrorMesh.Transform.Position.z + -1;
	textureCamera.Initialize();

	float cubeDirection = 0.02;

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
		DirectX::XMVECTOR I = DirectX::XMVectorSubtract(camera.LookAtPosition, camera.EyePosition);
		textureCamera.LookAtPosition = DirectX::XMVector3Reflect(I, DirectX::XMVectorSet(0, 0, 1, 0));
		textureCamera.Update(g_mouseState);
		sceneLights.Update();

		cubeMesh.Transform.Position.x += cubeDirection;
		cubeMesh.Transform.Position.y += cubeDirection;
		cubeMesh.Transform.Position.z += cubeDirection;
		if (cubeMesh.Transform.Position.y <= 0)
		{
			cubeDirection = 0.01;
		}
		else if (cubeMesh.Transform.Position.y >= 1.5)
		{
			cubeDirection = -0.01;
		}
		cubeMesh.Update();
		floorMesh.Update();
		reflectiveCubeMesh.Update();
		refractionCubeMesh.Update();
		mirrorMesh.Update();

		for (int i = 0; i < 5; i++)
		{
			unlitMesh[i].Transform.Position = sceneLights.GetPointLights(i).Position;
			unlitMesh[i].Transform.Scale = DirectX::XMFLOAT3(0.2f, 0.2f, 0.2f);
			unlitMesh[i].Material.DiffuseColor = sceneLights.GetPointLights(i).Color;
			unlitMesh[i].Material.Intensity = sceneLights.GetPointLights(i).Intensity;
			unlitMesh[i].Update();
		}

		renderer.Begin();

		if (true)
		{
			renderTarget.Use();

			// DRAW
			cubeMesh.Draw(textureCamera, sceneLights);
			floorMesh.Draw(textureCamera, sceneLights);
			reflectiveCubeMesh.Draw(textureCamera);
			refractionCubeMesh.Draw(textureCamera);
			skybox.Draw(textureCamera);

			renderer.DrawToScreenTexture();
		}

		// DRAW
		cubeMesh.Draw(camera, sceneLights);
		floorMesh.Draw(camera, sceneLights);
		for (int i = 0; i < 5; i++)
		{
			unlitMesh[i].Draw(camera);
		}
		reflectiveCubeMesh.Draw(camera);
		refractionCubeMesh.Draw(camera);
		mirrorMesh.Draw(camera, sceneLights);
		skybox.Draw(camera);
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