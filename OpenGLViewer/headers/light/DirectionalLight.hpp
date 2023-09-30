#ifndef DIRECTIONAL_LIGHT_HPP

#define DIRECTIONAL_LIGHT_HPP

#include <glm/glm.hpp>

namespace Viewer
{
    struct DirectionalLight
    {
        /// @brief The direction of the light.
        glm::vec3 Direction;

        /// @brief The intensity of the light.
        float Intensity;

        /// @brief The color of the light.
        glm::vec3 Color;
    };
}

#endif 