#pragma once

#include <vector>

namespace Viewer
{
	struct Geometry
	{
		std::vector<uint16_t> indices;
		std::vector<float> positionVertices;

		/// <summary>
		/// Creates the geometry for the quad.
		/// </summary>
		static Geometry CreateQuadGeometry();
	};
}