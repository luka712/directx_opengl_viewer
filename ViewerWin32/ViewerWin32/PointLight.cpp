#include "PointLight.hpp"

namespace Viewer
{

	PointLight::PointLight(DirectX::XMFLOAT3 pos, float intensity, DirectX::XMFLOAT3 color)
	{
		Position = pos;
		Intensity = intensity;
		Color = color;
	}

	PointLight::PointLight()
	{
		Color = { 1.0f, 1.0f, 1.0f };
		Position = { 0.0f, 3.0f, 0.0f };
		Intensity = 0.3f;
	}

}
