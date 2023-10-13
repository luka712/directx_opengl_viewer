#include "PointLight.hpp"

namespace Viewer
{

	PointLight::PointLight(DirectX::XMFLOAT3 pos, float intensity, DirectX::XMFLOAT3 color)
	{
		Position = pos;
		Intensity = intensity;
		Color = color;
		AttenuationConstant = 1;
		AttenuationLinear = 0.09;
		AttenuationQuadratic = 0.032;
	}

	PointLight::PointLight()
	{
		Color = { 1.0f, 1.0f, 1.0f };
		Position = { 0.0f, 3.0f, 0.0f };
		Intensity = 1.0f;
		AttenuationConstant = 1;
		AttenuationLinear = 0.09;
		AttenuationQuadratic = 0.032;
	}

}
