#include "camera/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Viewer
{
	Camera::Camera(float aspectRatio)
	{
		m_eyePosition = glm::vec3(3, 3, -3);
		m_lookAtPosition = glm::vec3(0, 0, 0);
		m_upVector = glm::vec3(0, 1, 0);
		m_projectionMatrix = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 1000.0f);
		m_viewMatrix = glm::lookAt(m_eyePosition, m_lookAtPosition, m_upVector);
		m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void Camera::Initialize()
	{
		m_cameraBuffer.Initialize();
		m_skyboxCameraBuffer.Initialize();
	}

	void Camera::Update(MouseState &mouseState)
	{
		// regular camera data
		m_viewMatrix = glm::lookAt(m_eyePosition, m_lookAtPosition, m_upVector);
		m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;

		CameraData data;
		data.ProjectionViewMatrix = m_projectionViewMatrix;
		data.EyePosition = m_eyePosition;
		m_cameraBuffer.Update(&data);

		// for skybox , get rid of translation
		glm::mat4x4 skyboxViewCamera = glm::mat4x4(glm::mat3x3(m_viewMatrix));
		glm::mat4x4 skyboxProjectionViewMatrix = m_projectionMatrix * skyboxViewCamera;
		m_skyboxCameraBuffer.Update(&skyboxProjectionViewMatrix);
	}
}