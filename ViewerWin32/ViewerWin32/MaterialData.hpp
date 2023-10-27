#pragma once

#include <DirectXMath.h>

namespace Viewer
{
	struct UnlitMaterialData
	{
		DirectX::XMFLOAT3 Color;
		float Intensity;
	};

	struct MaterialData
	{
		float DiffuseCoefficient;
		float SpecularCoefficient;
		float Shininess;
	};

	struct RefractionMaterialData
	{
		float RefractionIndex;
	};
}