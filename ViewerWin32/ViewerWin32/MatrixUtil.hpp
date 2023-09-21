#pragma once

#include <DirectXMath.h>

namespace Viewer
{
	class MatrixUtil final 
	{
	public:
	 	static void Print(const DirectX::XMMATRIX& matrix);
	};
}
