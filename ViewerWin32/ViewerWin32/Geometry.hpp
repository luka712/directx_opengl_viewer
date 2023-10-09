#pragma once

#include <vector>

namespace Viewer
{
	struct Geometry
	{
		std::vector<uint16_t> indices;
		std::vector<float> positionVertices;
		std::vector<float> colorVertices;
		std::vector<float> textureVertices;
		std::vector<float> normalVertices;

		/// <summary>
		/// Creates the geometry for the quad.
		/// </summary>
		static Geometry CreateQuadGeometry();

		/// <summary>
		/// Creates the geometry for the cube.
		/// </summary>
		/// <returns></returns>
		static Geometry CreateCubeGeometry();

		/// <summary>
		/// Creates the geometry for the skybox.
		/// </summary>
		/// <returns></returns>
		static Geometry CreateSkyboxGeometry();
	};
}