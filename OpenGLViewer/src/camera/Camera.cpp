#include "camera/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Viewer
{
	Camera::Camera(float aspectRatio)
	{
		EyePosition = glm::vec3(3, 3, -3);
		LootAtPosition = glm::vec3(0, 0, 0);
		m_upVector = glm::vec3(0, 1, 0);
		m_projectionMatrix = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 1000.0f);
		ViewMatrix = glm::lookAt(EyePosition, LootAtPosition, m_upVector);
		m_projectionViewMatrix = m_projectionMatrix * ViewMatrix;
	}

	void Camera::Initialize()
	{
		m_cameraBuffer.Initialize();
		m_skyboxCameraBuffer.Initialize();
		m_projectionBuffer.Initialize();
	}

	void Camera::Update(MouseState &mouseState)
	{
		// regular camera data
		ViewMatrix = glm::lookAt(EyePosition, LootAtPosition, m_upVector);
		m_projectionViewMatrix = m_projectionMatrix * ViewMatrix;

		CameraData data;
		data.ProjectionViewMatrix = m_projectionViewMatrix;
		data.EyePosition = EyePosition;
		m_cameraBuffer.Update(&data);

		// for skybox , get rid of translation
		glm::mat4x4 skyboxViewCamera = glm::mat4x4(glm::mat3x3(ViewMatrix));
		glm::mat4x4 skyboxProjectionViewMatrix = m_projectionMatrix * skyboxViewCamera;
		m_skyboxCameraBuffer.Update(&skyboxProjectionViewMatrix);

		// for projection camera
		m_projectionBuffer.Update(&m_projectionMatrix);
	}

	

}