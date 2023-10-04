#ifndef ORBIT_CAMERA_HPP

#define ORBIT_CAMERA_HPP

#include "camera/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Viewer
{
    class OrbitCamera final : public Camera
    {
    private:
        float m_radius;
        float m_inclination;
        float m_azimuth;

        void ControlZoom(MouseState &mouseState);
        void ControlIncline(MouseState &mouseState);
        void ControlAzimuth(MouseState &mouseState);

    public:
        OrbitCamera(float aspectRatio, float radius = 3, float inclination = 0, float azimuth = 0);

        // @brief Update the camera.
        void Update(MouseState &mouseState) override;
    };
}

#endif