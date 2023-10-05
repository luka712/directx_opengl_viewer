#include "light/DirectionalLight.hpp"

namespace Viewer
{
    DirectionalLight::DirectionalLight() : Direction(glm::vec3(0.0f, -1.0f, 0.0f)),
                                           Intensity(0.2f),
                                           Color(glm::vec3(1.0f, 1.0f, 1.0f)),
                                           _padding(0.0f)
    {
    }

    DirectionalLight::DirectionalLight(const glm::vec3 &direction, float intensity, const glm::vec3 &color) : Direction(direction),
                                                                                                              Intensity(intensity),
                                                                                                              Color(color),
                                                                                                              _padding(0.0f)
    {
    }
}