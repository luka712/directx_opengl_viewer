#include "transform/Transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Viewer
{
	Transform::Transform()
	{
		Scale = glm::vec3(1, 1, 1);
		Position = glm::vec3(0, 0, 0);
		Rotation = glm::vec3(0, 0, 0);
	}

	void Transform::Initialize()
	{
		m_transformBuffer.Initialize(2);

	}

	void Transform::Update()
	{
		glm::mat4x4 translation = glm::translate(glm::mat4x4(1.0f), Position);
		glm::mat4x4 rotationX = glm::rotate(glm::mat4x4(1.0f), glm::radians(Rotation.x), glm::vec3(1, 0, 0));
		glm::mat4x4 rotationY = glm::rotate(glm::mat4x4(1.0f), glm::radians(Rotation.y), glm::vec3(0, 1, 0));
		glm::mat4x4 rotationZ = glm::rotate(glm::mat4x4(1.0f), glm::radians(Rotation.z), glm::vec3(0, 0, 1));
		glm::mat4x4 rotation = rotationX * rotationY * rotationZ;
		glm::mat4x4 scale = glm::scale(glm::mat4x4(1.0f), Scale);

		glm::mat4x4 modelMatrix = translation * rotation * scale;
		glm::mat4x4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

		glm::mat4x4 matrices[2] = { modelMatrix, normalMatrix };
		m_transformBuffer.Update(&matrices[0], 2);
	}
}