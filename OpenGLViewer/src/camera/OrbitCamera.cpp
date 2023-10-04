#include "camera/OrbitCamera.hpp"
#include <algorithm>

#define PI 3.1415926535897932384626433832795f
#define HALP_PI 1.5707963267948966192313216916398f

namespace Viewer
{

	OrbitCamera::OrbitCamera(float aspectRatio, float radius, float inclination, float azimuth)
		: Camera(aspectRatio), m_radius(radius), m_inclination(inclination), m_azimuth(azimuth)
	{
	}

	void OrbitCamera::ControlZoom(MouseState& mouseState)
	{
		// zoom
		if (mouseState.DeltaWheelY > 0)
		{
			m_radius -= 0.1;
		}
		else if (mouseState.DeltaWheelY < 0)
		{
			m_radius += 0.1;
		}

		// limit radius to 0.1
		if (m_radius < 0.1)
		{
			m_radius = 0.1;
		}
	}

	void OrbitCamera::ControlIncline(MouseState& mouseState)
	{
		// inclination

		m_inclination += 0.01f * mouseState.DeltaY;


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

	void OrbitCamera::ControlAzimuth(MouseState& mouseState)
	{
		m_azimuth += 0.01f * mouseState.DeltaX;
	}

	void OrbitCamera::Update(MouseState& mouseState)
	{
		ControlZoom(mouseState);
		if (mouseState.LeftButton)
		{
			ControlIncline(mouseState);
			ControlAzimuth(mouseState);
		}

		float x = m_radius * cos(m_inclination) * cos(m_azimuth);
		float y = m_radius * sin(m_inclination);
		float z = m_radius * cos(m_inclination) * sin(m_azimuth);
		m_eyePosition = glm::vec3(x, y, z);

		Camera::Update(mouseState);
	}
}