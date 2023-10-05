#pragma once

#include <DirectXMath.h>

namespace Viewer
{
	struct PointLight
	{
		/// <summary>
		/// The position of the light
		/// </summary>
		DirectX::XMFLOAT3 Position;

		/// <summary>
		/// The intensity of the light
		/// </summary>
		float Intensity;

		/// <summary>
		/// The color of the light
		/// </summary>
		DirectX::XMFLOAT3 Color;

		PointLight(DirectX::XMFLOAT3 pos, float intensity, DirectX::XMFLOAT3 color);

		PointLight();

	private:
		/// <summary>
		/// Padding to make the struct size a multiple of 16 bytes
		/// </summary>
		float _padding = 0.0f;
	};
}