#include "DirectionalLight.hpp"

namespace Viewer
{
	DirectionalLight::DirectionalLight(DirectX::XMFLOAT3 direction, float intensity, DirectX::XMFLOAT3 color) :
		Direction(direction),
		Intensity(intensity),
		Color(color)
	{
	}

	DirectionalLight::DirectionalLight()
	{
		Color = { 1.0f, 1.0f, 1.0f };
		Direction = { 0.0f, -1.0f, 0.0f };
		Intensity = 0.3f;
	}
}