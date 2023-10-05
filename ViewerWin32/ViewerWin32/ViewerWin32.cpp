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

	// TOOD: MOVE TO TEXTURE LOADER
	Viewer::ImageLoader imageLoader;
	Viewer::ImageData* imageData = imageLoader.Load("crate_texture.png");
	Viewer::Texture2D diffuseTexture(renderer.GetDevice());
	diffuseTexture.Initialize(imageData->Data, imageData->Width, imageData->Height);
	delete imageData;

	Viewer::ImageData* imageData2 = imageLoader.Load("crate_specular.png");
	Viewer::Texture2D specularTexture(renderer.GetDevice());
	specularTexture.Initialize(imageData2->Data, imageData2->Width, imageData2->Height);
	delete imageData2;

	Viewer::ImageData* imageData3 = imageLoader.Load("wood_diffuse.png");
	Viewer::Texture2D woodDiffuseTexture(renderer.GetDevice());
	woodDiffuseTexture.Initialize(imageData3->Data, imageData3->Width, imageData3->Height);
	delete imageData3;

	Viewer::ImageData* imageData4 = imageLoader.Load("wood_specular.png");
	Viewer::Texture2D woodSpecularTexture(renderer.GetDevice());
	woodSpecularTexture.Initialize(imageData4->Data, imageData4->Width, imageData4->Height);
	delete imageData4;

	Viewer::StandardMaterial material(renderer.GetDevice(), renderer.GetDeviceContext());
	material.Initialize();
	material.DiffuseTexture = &diffuseTexture;
	material.SpecularTexture = &specularTexture;
	material.DiffuseCoefficient = 0.5f;
	material.SpecularCoefficient = 3.0f;
	material.Shininess = 12.0f;

	Viewer::StandardMaterial floorMaterial(renderer.GetDevice(), renderer.GetDeviceContext());
	floorMaterial.Initialize();
	floorMaterial.DiffuseTexture = &woodDiffuseTexture;
	floorMaterial.SpecularTexture = &woodSpecularTexture;
	floorMaterial.DiffuseCoefficient = 0.5f;
	floorMaterial.SpecularCoefficient = 3.0f;
	floorMaterial.Shininess = 24.0f;

	Viewer::Geometry geometry = Viewer::Geometry::CreateCubeGeometry();
	Viewer::GeometryBuffer geometryBuffer;
	geometryBuffer.Initialize(renderer.GetDevice(),
		geometry.positionVertices,
		geometry.indices,
		geometry.textureVertices,
		geometry.normalVertices,
		geometry.colorVertices);

	Viewer::Geometry floorGeometry = Viewer::Geometry::CreateQuadGeometry();
	Viewer::GeometryBuffer floorGeometryBuffer;
	floorGeometryBuffer.Initialize(renderer.GetDevice(),
				floorGeometry.positionVertices,
				floorGeometry.indices,
				floorGeometry.textureVertices,
				floorGeometry.normalVertices,
				floorGeometry.colorVertices);


	Viewer::Transform transform(renderer.GetDevice(), renderer.GetDeviceContext());
	transform.Initialize();

	Viewer::Transform floorTransform(renderer.GetDevice(), renderer.GetDeviceContext());
	floorTransform.Initialize();
	floorTransform.Position.y = -0.5;
	floorTransform.Scale.x = 10;
	floorTransform.Scale.y = 10;
	floorTransform.Rotation.x = 90;


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

		camera.Update(g_mouseState);
		sceneLights.Update();
		transform.Update();
		floorTransform.Update();
		

		renderer.Begin();

		// DRAW
		material.Use();

		material.UpdateSelfProperties();
		material.UpdateCameraProperties(camera);
		material.UpdateTransformProperties(transform);
		material.UpdateLightsProperties(
			sceneLights.GetAmbientLightBuffer(), 
			sceneLights.GetDirectionalLightsBuffer(), 
			sceneLights.GetPointLightsBuffer());

		geometryBuffer.Draw(renderer.GetDeviceContext());

		// DRAW
		floorMaterial.Use();

		floorMaterial.UpdateSelfProperties();
		floorMaterial.UpdateCameraProperties(camera);
		floorMaterial.UpdateTransformProperties(floorTransform);
		floorMaterial.UpdateLightsProperties(
			sceneLights.GetAmbientLightBuffer(),
			sceneLights.GetDirectionalLightsBuffer(),
			sceneLights.GetPointLightsBuffer());

		floorGeometryBuffer.Draw(renderer.GetDeviceContext());

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