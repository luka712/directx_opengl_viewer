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

        void Initialize(std::vector<float> &positionVertices,
            std::vector<uint16_t> &indices,
            std::vector<float>&textureCoords,
            std::vector<float>&normalVertices,
            std::vector<float>&vertexColorData);

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
        unsigned int m_vertexNormalBuffer;
        unsigned int m_vertexColorBuffer;
        
        size_t m_indexCount;
        size_t m_verticesCount;
    };
}

#endif