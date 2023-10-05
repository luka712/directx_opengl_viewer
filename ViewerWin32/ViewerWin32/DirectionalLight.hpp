#pragma once

#include <DirectXMath.h>

namespace Viewer
{
	struct DirectionalLight
	{
		/// <summary>
		/// The direction of the light
		/// </summary>
		DirectX::XMFLOAT3 Direction;

		/// <summary>
		/// The intensity of the light
		/// </summary>
		float Intensity;

		/// <summary>
		/// The color of the light
		/// </summary>
		DirectX::XMFLOAT3 Color;

		DirectionalLight(DirectX::XMFLOAT3 direction, float intensity, DirectX::XMFLOAT3 color);

		DirectionalLight();

	private:
			/// <summary>
			/// Padding to make the struct size a multiple of 16 bytes
			/// </summary>
		float _padding = 0.0f;
	};
}