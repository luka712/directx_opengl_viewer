#include "Camera.hpp"

namespace Viewer {


	Camera::Camera(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, float aspectRatio)
	{
		m_eyePosition = DirectX::XMVectorSet(3, 3, -3, 0);
		m_lookAtPosition = DirectX::XMVectorSet(0, 0, 0, 0);
		m_upVector = DirectX::XMVectorSet(0, 1, 0, 0);

		// pi/3.0 = 60 degrees
		m_projectionMatrix = DirectX::XMMatrixPerspectiveFovRH(DirectX::XM_PI / 3.0, aspectRatio, 0.1, 1000);
		m_viewMatrix = DirectX::XMMatrixLookAtRH(m_eyePosition, m_lookAtPosition, m_upVector);
		m_projectionViewMatrix = DirectX::XMMatrixTranspose(m_viewMatrix * m_projectionMatrix);

		// DirectX::XMMATRIX projectionViewMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterRH(-10, 10, -5, 5, 1, -1));


		m_cameraBuffer = new ConstantBuffer<CameraData>(device, deviceContext);
		m_skyboxCameraBuffer = new ConstantBuffer<DirectX::XMMATRIX>(device, deviceContext);
	}


	void Camera::Initialize()
	{
		m_cameraBuffer->Initialize();
		m_skyboxCameraBuffer->Initialize();
	}

	void Camera::Update(MouseState& g_mouseState)
	{
		m_viewMatrix = DirectX::XMMatrixLookAtRH(m_eyePosition, m_lookAtPosition, m_upVector);
		m_projectionViewMatrix = DirectX::XMMatrixTranspose(m_viewMatrix * m_projectionMatrix);
		CameraData cameraData = { m_projectionViewMatrix, m_eyePosition };
		m_cameraBuffer->Update(&cameraData, 1);

		// Update skybox camera
		DirectX::XMFLOAT3X3 viewMatrix3x3 = DirectX::XMFLOAT3X3(
			m_viewMatrix.r[0].m128_f32[0], m_viewMatrix.r[0].m128_f32[1], m_viewMatrix.r[0].m128_f32[2],
			m_viewMatrix.r[1].m128_f32[0], m_viewMatrix.r[1].m128_f32[1], m_viewMatrix.r[1].m128_f32[2],
			m_viewMatrix.r[2].m128_f32[0], m_viewMatrix.r[2].m128_f32[1], m_viewMatrix.r[2].m128_f32[2]
		);
		DirectX::XMMATRIX skyboxViewCamera = DirectX::XMMATRIX(
			viewMatrix3x3._11, viewMatrix3x3._12, viewMatrix3x3._13, 0,
			viewMatrix3x3._21, viewMatrix3x3._22, viewMatrix3x3._23, 0,
			viewMatrix3x3._31, viewMatrix3x3._32, viewMatrix3x3._33, 0,
			0, 0, 0, 1
		);
		DirectX::XMMATRIX skyboxProjectionViewMatrix = DirectX::XMMatrixTranspose(skyboxViewCamera * m_projectionMatrix);
		m_skyboxCameraBuffer->Update(&skyboxProjectionViewMatrix, 1);
	}

}
