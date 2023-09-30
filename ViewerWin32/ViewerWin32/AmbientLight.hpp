#pragma once

#include <DirectXMath.h>

namespace Viewer
{
	struct AmbientLight
	{
		/// <summary>
		/// The intensity of the light
		/// </summary>
		float Intensity;

		/// <summary>
		/// The color of the light
		/// </summary>
		DirectX::XMFLOAT3 Color;
	};
}