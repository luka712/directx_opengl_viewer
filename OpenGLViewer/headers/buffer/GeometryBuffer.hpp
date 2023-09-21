#ifndef BUFFER_HPP

#define BUFFER_HPP

#include <glad/glad.h>
#include <vector>

namespace Viewer
{
    class GeometryBuffer final
    {
    public:
        ~GeometryBuffer();

        void Initialize(std::vector<float> &positionVertices, std::vector<uint16_t> &indices);
        void Bind();
        void Unbind();

    private:
        unsigned int m_vaoID;
        unsigned int m_indexBuffer;
        unsigned int m_vertexPositionBuffer;
    };
}

#endif