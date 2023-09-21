#ifndef GEOEMTRY_HPP

#define GEOEMTRY_HPP

#include <vector>

namespace Viewer
{
    struct Geometry final
    {
        std::vector<uint16_t> indices;
        std::vector<float> positionVertices;

        /**
         * @brief Create a quad geometry.
         */
        static Geometry CreateQuadGeometry();
    };
}

#endif