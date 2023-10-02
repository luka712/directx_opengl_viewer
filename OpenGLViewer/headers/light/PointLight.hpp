#ifndef POINT_LIGHT_HPP

#define POINT_LIGHT_HPP

#include <glm/glm.hpp>

namespace Viewer
{
    struct PointLight
    {
        /// @brief The position of the light.
        glm::vec3 Position;

        /// @brief The intensity of the light.
        float Intensity;

        /// @brief The color of the light.
        glm::vec3 Color;
    };
}

#endif 