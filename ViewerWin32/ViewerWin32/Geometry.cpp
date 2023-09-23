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

	Geometry Geometry::CreateCubeGeometry()
	{
		Geometry geometry;

		geometry.positionVertices = {
				// Front face
			  -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5,

			  // Back face
			  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5,

			  // Top face
			  -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5,

			  // Bottom face
			  -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5,

			  // Right face
			  0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5,

			  // Left face
			  -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5,
		};

		geometry.colorVertices = {
			// Left face 
			0.0, 0.0, 1.0, 1.0, // blue
			0.0, 0.0, 1.0, 1.0, // blue
			0.0, 0.0, 1.0, 1.0, // blue
			0.0, 0.0, 1.0, 1.0, // blue

			// Right face
			1.0, 0.0, 0.0, 1.0, // red
			1.0, 0.0, 0.0, 1.0, // red
			1.0, 0.0, 0.0, 1.0, // red
			1.0, 0.0, 0.0, 1.0, // red

			// Top face
			0.0, 1.0, 0.0, 1.0, // green
			0.0, 1.0, 0.0, 1.0, // green
			0.0, 1.0, 0.0, 1.0, // green
			0.0, 1.0, 0.0, 1.0, // green

			// Bottom face
			1.0, 1.0, 0.0, 1.0, // yellow
			1.0, 1.0, 0.0, 1.0, // yellow
			1.0, 1.0, 0.0, 1.0, // yellow
			1.0, 1.0, 0.0, 1.0, // yellow

			// Front face
			0.0, 1.0, 1.0, 1.0, // cyan
			0.0, 1.0, 1.0, 1.0, // cyan
			0.0, 1.0, 1.0, 1.0, // cyan
			0.0, 1.0, 1.0, 1.0, // cyan

			// Back face
			1.0, 0.0, 1.0, 1.0, // magenta
			1.0, 0.0, 1.0, 1.0, // magenta
			1.0, 0.0, 1.0, 1.0, // magenta
			1.0, 0.0, 1.0, 1.0, // magenta


		};

		geometry.indices = {
			// front face
			0, 1, 2, // first triangle
			0, 2, 3, // second triangle

			// back face
			4, 5, 6, // first triangle
			4, 6, 7, // second triangle

			// left face
			8, 9, 10, // first triangle
			8, 10, 11, // second triangle

			// right face
			12, 13, 14, // first triangle
			12, 14, 15, // second triangle

			// top face
			16, 17, 18, // first triangle
			16, 18, 19, // second triangle

			// bottom face
			20, 21, 22, // first triangle
			20, 22, 23, // second triangle
		};

		return geometry;
	}
}