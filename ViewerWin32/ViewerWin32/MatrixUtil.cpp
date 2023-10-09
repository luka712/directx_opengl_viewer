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


	// Function to create XMFLOAT3x3 from XMMATRIX
	DirectX::XMFLOAT3X3 MatrixUtil::Create3x3(const DirectX::XMMATRIX& matrix)
	{
		DirectX::XMFLOAT3X3 result;

		// Access components of the XMMATRIX and assign them to XMFLOAT3x3
		result._11 = matrix.r[0].m128_f32[0];
		result._12 = matrix.r[0].m128_f32[1];
		result._13 = matrix.r[0].m128_f32[2];

		result._21 = matrix.r[1].m128_f32[0];
		result._22 = matrix.r[1].m128_f32[1];
		result._23 = matrix.r[1].m128_f32[2];

		result._31 = matrix.r[2].m128_f32[0];
		result._32 = matrix.r[2].m128_f32[1];
		result._33 = matrix.r[2].m128_f32[2];

		return result;
	}

	// Function to create XMFLOAT4x4 from XMFLOAT3x3
	DirectX::XMMATRIX MatrixUtil::Create4x4(const DirectX::XMFLOAT3X3& matrix3x3)
	{
		return DirectX::XMMATRIX(
			matrix3x3._11, matrix3x3._12, matrix3x3._13, 0.0f,
			matrix3x3._21, matrix3x3._22, matrix3x3._23, 0.0f,
			matrix3x3._31, matrix3x3._32, matrix3x3._33, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


}