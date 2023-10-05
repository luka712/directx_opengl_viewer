#include "light/PointLight.hpp"

Viewer::PointLight::PointLight()
{
	Intensity = 0;
	Position = glm::vec3(0, 3, 0);
	Color = glm::vec3(1, 1, 1);
}
