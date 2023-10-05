#ifndef SCENE_LIGHTS_HPP

#define SCENE_LIGHTS_HPP

#include "buffer/UniformBuffer.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"
#include <exception>

namespace Viewer
{
    class SceneLights
    {
    public:
        /// @brief Initializes the scene lights.
        void Initialize();

        /// @brief Updates the scene lights.
        void Update();

        /// @brief Gets the ambient light.
        /// @return The ambient light.
        AmbientLight &GetAmbientLight() { return m_ambientLight; }

        /// @brief Gets the directional lights.
        /// @return The directional lights.
        DirectionalLight &GetDirectionalLights(int index)
        {
            if (index < 0 || index > 2)
            {
                throw std::exception("Index out of range.");
            }
        }

        /// @brief Gets the point lights.
        /// @return The point lights.
        PointLight &GetPointLights(int index)
        {
            if (index < 0 || index > 4)
            {
                throw std::exception("Index out of range.");
            }
        }

        /// @brief Gets the ambient light buffer.
        UniformBuffer<Viewer::AmbientLight> &GetAmbientLightBuffer() { return m_ambientLightBuffer; }

        /// @brief Gets the directional lights buffer.
        UniformBuffer<Viewer::DirectionalLight> &GetDirectionalLightsBuffer() { return m_directionalLightsBuffer; }

        /// @brief Gets the point lights buffer.
        UniformBuffer<Viewer::PointLight> &GetPointLightsBuffer() { return m_pointLightsBuffer; }

    private:
        AmbientLight m_ambientLight;
        DirectionalLight m_directionalLights[3];
        PointLight m_pointLights[5];

        UniformBuffer<Viewer::AmbientLight> m_ambientLightBuffer;
        UniformBuffer<Viewer::DirectionalLight> m_directionalLightsBuffer;
        UniformBuffer<Viewer::PointLight> m_pointLightsBuffer;
    };
}

#endif // SCENE_LIGHTS_HPP