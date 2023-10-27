#pragma once

#include <DirectXMath.h>
#include "ConstantBuffer.hpp"
#include "MouseState.hpp"

namespace Viewer
{

	struct CameraData
	{
		DirectX::XMMATRIX ProjectionViewMatrix;
		DirectX::XMVECTOR EyePosition;
	};

	class Camera
	{
	protected:
		DirectX::XMVECTOR m_upVector;

		DirectX::XMMATRIX m_projectionMatrix;
		DirectX::XMMATRIX m_projectionViewMatrix;

		ConstantBuffer<CameraData>* m_cameraBuffer;
		ConstantBuffer<DirectX::XMMATRIX>* m_skyboxCameraBuffer;
		ConstantBuffer<DirectX::XMMATRIX>* m_projectionBuffer;

	public:
		Camera(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, float aspectRatio);

		/// <summary>
		/// The position of the camera.
		/// </summary>
		DirectX::XMVECTOR EyePosition;

		/// <summary>
		/// The look at position of the camera.
		/// </summary>
		DirectX::XMVECTOR LookAtPosition;

		DirectX::XMMATRIX ViewMatrix;

		/// <summary>
		/// Initialize the camera.
		/// </summary>
		virtual void Initialize();

		/// <summary>
		/// Update the camera.
		/// </summary>
		virtual void Update(MouseState& g_mouseState);


		inline DirectX::XMVECTOR GetUpVector() const { return m_upVector; }


		/// <summary>
		/// Gets the buffer containing the camera data.
		/// </summary>
		inline ConstantBuffer<CameraData>* GetCameraBuffer() { return m_cameraBuffer; }

		inline ConstantBuffer<DirectX::XMMATRIX>* const GetSkyboxCameraBuffer() const { return m_skyboxCameraBuffer; }

		inline ConstantBuffer<DirectX::XMMATRIX>* const GetProjectionBuffer() const { return m_projectionBuffer; }




	};
}