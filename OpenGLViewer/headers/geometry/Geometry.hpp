#ifndef GEOEMTRY_HPP

#define GEOEMTRY_HPP

#include <vector>

namespace Viewer
{
    struct Geometry final
    {
        std::vector<uint16_t> indices;
        std::vector<float> positionVertices;
        std::vector<float> colorVertices;
        std::vector<float> textureVertices;
        std::vector<float> normalVertices;

        /**
         * @brief Create a quad geometry.
         */
        static Geometry CreateQuadGeometry();

        /**
         * @brief Create a cube geometry.
        */
        static Geometry CreateCubeGeometry();
    };
}

#endif