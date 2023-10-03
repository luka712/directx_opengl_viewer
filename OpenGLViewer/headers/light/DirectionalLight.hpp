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

		/// @brief Padding for the structure.
		float _padding;

		/// @brief Constructor.
		/// @param direction The direction of the light.
		/// @param intensity The intensity of the light.
		/// @param color The color of the light.
		DirectionalLight(const glm::vec3& direction, float intensity, const glm::vec3& color) :
			Direction(direction),
			Intensity(intensity),
			Color(color)
		{
		}
    };
}

#endif 