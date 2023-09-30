#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include <glm/glm.hpp>

namespace Viewer 
{
    struct AmbientLight 
    {
        /// @brief The intensity of the light.
        float Intensity;

        /// @brief The color of the light.
        glm::vec3 Color;
    };
}

#endif // AMBIENT_LIGHT_HPP