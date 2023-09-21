#include "Geometry.hpp"

namespace Viewer
{
	Geometry Geometry::CreateQuadGeometry()
	{
		Geometry geometry;

		geometry.positionVertices = 
		{
			// top left
			-0.5f, 0.5f, 0.5f,
			// top right
			0.5f, 0.5f, 0.5f,
			// bottom right 
			0.5f, -0.5f, 0.5f,
			// bottom left
			-0.5f, -0.5f, 0.5f,
		};

		geometry.indices =
		{
			0, 1, 2, // first triangle
			0, 2, 3, // second triangle
		};
		return geometry;
	}
}