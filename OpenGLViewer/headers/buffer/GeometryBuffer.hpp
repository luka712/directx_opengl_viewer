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

        void Initialize(std::vector<float> &positionVertices, std::vector<uint16_t> &indices, std::vector<float>&textureCoords);

        /**
         * @brief Bind the buffer to the current OpenGL context. Can be skipped if @ref Draw is called.
        */
        void Bind();
        void Unbind();

        /**
         * @brief Draw the buffer. Bind is also called withing draw.
        */
        void Draw();

    private:
        unsigned int m_vaoID;
        unsigned int m_indexBuffer;
        unsigned int m_vertexPositionBuffer;
        unsigned int m_vertexTextureBuffer;
        
        size_t m_indexCount;
    };
}

#endif