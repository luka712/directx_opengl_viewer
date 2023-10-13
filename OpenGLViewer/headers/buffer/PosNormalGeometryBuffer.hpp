#ifndef POS_NORMAL_GEOMETRY_BUFFER_HPP

#define POS_NORMAL_GEOMETRY_BUFFER_HPP

#include <glad/glad.h>
#include <vector>

namespace Viewer
{
    class PosNormalGeometryBuffer final
    {
    public:
        ~PosNormalGeometryBuffer();

        void Initialize(std::vector<float> &positionVertices,
                        std::vector<uint16_t> &indices,
                        std::vector<float> &normalVertices);

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
        unsigned int m_vertexNormalBuffer;

        size_t m_verticesCount;
        size_t m_indexCount;
    };
}

#endif // !POS_NORMAL_GEOMETRY_BUFFER_HPP