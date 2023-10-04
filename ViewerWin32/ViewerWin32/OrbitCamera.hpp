#pragma once

#include "Camera.hpp"

namespace Viewer
{
    class OrbitCamera final : public Camera
    {
    private:
        float m_radius;
        float m_inclination;
        float m_azimuth;

        void ControlZoom(MouseState& g_mouseState);
        void ControlIncline(MouseState& g_mouseState);
        void ControlAzimuth(MouseState& g_mouseState);

    public:
        OrbitCamera(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, float aspectRatio, float radius = 3, float inclination = 0, float azimuth = 0);

        // @brief Update the camera.
        void Update(MouseState& g_mouseState) override;
    };
}
