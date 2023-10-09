#pragma once

#include <DirectXMath.h>

namespace Viewer
{
	class MatrixUtil final 
	{
	public:
	 	static void Print(const DirectX::XMMATRIX& matrix);

		static DirectX::XMFLOAT3X3 Create3x3(const DirectX::XMMATRIX& matrix);

		static DirectX::XMMATRIX Create4x4(const DirectX::XMFLOAT3X3& matrix3x3);
	};
}
