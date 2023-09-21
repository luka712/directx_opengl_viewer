#include "MatrixUtil.hpp"

#include <iostream>
#include <string>
#include <windows.h>

namespace Viewer
{
	void MatrixUtil::Print(const DirectX::XMMATRIX& matrix)
	{
		std::string str = "";

		// print matrix row by row
		for (int i = 0; i < 4; ++i)
		{
			str += "[ ";
			for (int j = 0; j < 4; ++j)
			{
				str += std::to_string(matrix.r[i].m128_f32[j]) + " ";
			}
			str += "]\n";
		}

		std::wstring wStr = std::wstring(str.begin(), str.end());
		OutputDebugStringW(wStr.c_str());
	}

}