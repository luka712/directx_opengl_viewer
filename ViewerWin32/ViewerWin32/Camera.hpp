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
		DirectX::XMVECTOR m_eyePosition;
		DirectX::XMVECTOR m_lookAtPosition;
		DirectX::XMVECTOR m_upVector;

		DirectX::XMMATRIX m_projectionMatrix;
		DirectX::XMMATRIX m_viewMatrix;
		DirectX::XMMATRIX m_projectionViewMatrix;

		ConstantBuffer<CameraData> *m_cameraBuffer;

	public:
		Camera(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, float aspectRatio);

		/// <summary>
		/// Initialize the camera.
		/// </summary>
		virtual void Initialize();

		/// <summary>
		/// Update the camera.
		/// </summary>
		virtual void Update(MouseState& g_mouseState);

		inline DirectX::XMVECTOR GetEyePosition() const { return m_eyePosition; }

		inline DirectX::XMVECTOR GetLookAtPosition() const { return m_lookAtPosition; }

		inline DirectX::XMVECTOR GetUpVector() const { return m_upVector; }

		inline DirectX::XMMATRIX GetViewMatrix() const { return m_viewMatrix; }

		/// <summary>
		/// Gets the buffer containing the camera data.
		/// </summary>
		inline ConstantBuffer<CameraData>* GetCameraBuffer() { return m_cameraBuffer; }



	};
}