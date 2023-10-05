#include "light/AmbientLight.hpp"

Viewer::AmbientLight::AmbientLight()
{
	Color = glm::vec3(1.0f, 1.0f, 1.0f);
	Intensity = 0.2f;
}
