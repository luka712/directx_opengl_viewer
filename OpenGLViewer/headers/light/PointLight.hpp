#ifndef POINT_LIGHT_HPP

#define POINT_LIGHT_HPP

#include <glm/glm.hpp>

namespace Viewer
{
    struct PointLight
    {
        PointLight();

        /// @brief The position of the light.
        glm::vec3 Position;

        /// @brief The intensity of the light.
        float Intensity;

        /// @brief The color of the light.
        glm::vec3 Color;

        /// @brief The constant term of attenuation of the light.
        float AttenuationConstant;

        /// @brief The linear term of attenuation of the light.
        float AttenuationLinear;

        /// @brief The quadratic term of attenuation of the light.
        float AttenuationQuadratic;

        float _padding[2];
    };
}

#endif