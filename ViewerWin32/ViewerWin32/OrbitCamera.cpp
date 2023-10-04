#include "OrbitCamera.hpp"
#include <algorithm>

#define PI 3.1415926535897932384626433832795f
#define HALP_PI 1.5707963267948966192313216916398f

namespace Viewer
{

	OrbitCamera::OrbitCamera(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext, float aspectRatio, float radius, float inclination, float azimuth)
		: Camera(device, deviceContext, aspectRatio), m_radius(radius), m_inclination(inclination), m_azimuth(azimuth)
	{

	}

	void OrbitCamera::ControlZoom(MouseState& g_mouseState)
	{
		// zoom
		if (g_mouseState.DeltaWheelY > 0)
		{
			m_radius -= 0.1;
		}
		else if (g_mouseState.DeltaWheelY < 0)
		{
			m_radius += 0.1;
		}

		// limit radius to 0.1
		if (m_radius < 0.1)
		{
			m_radius = 0.1;
		}
	}

	void OrbitCamera::ControlIncline(MouseState& g_mouseState)
	{
		// inclination

		m_inclination += 0.01f * g_mouseState.DeltaY;


		float maxInclination = HALP_PI - 0.1;
		if (m_inclination > maxInclination)
		{
			m_inclination = maxInclination;
		}
		else if (m_inclination < -maxInclination)
		{
			m_inclination = -maxInclination;
		}
	}

	void OrbitCamera::ControlAzimuth(MouseState& g_mouseState)
	{
		m_azimuth += 0.01f * g_mouseState.DeltaX;
	}

	void OrbitCamera::Update(MouseState& g_mouseState)
	{
		ControlZoom(g_mouseState);
		if (g_mouseState.LeftButton)
		{
			ControlIncline(g_mouseState);
			ControlAzimuth(g_mouseState);
		}

		float x = m_radius * cos(m_inclination) * cos(m_azimuth);
		float y = m_radius * sin(m_inclination);
		float z = m_radius * cos(m_inclination) * sin(m_azimuth);
		m_eyePosition = DirectX::XMVECTOR({ x, y, z, 0 });

		Camera::Update(g_mouseState);
	}
}