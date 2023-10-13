#include "light/PointLight.hpp"

Viewer::PointLight::PointLight()
{
	AttenuationConstant = 1;
	AttenuationLinear = 0.09;
	AttenuationQuadratic = 0.032;
	Intensity = 1;
	Position = glm::vec3(0, 3, 0);
	Color = glm::vec3(1, 1, 1);
}
