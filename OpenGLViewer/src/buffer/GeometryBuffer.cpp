#include "buffer/GeometryBuffer.hpp"
#include <glad/glad.h>

namespace Viewer
{
    void GeometryBuffer::Initialize(std::vector<float>& positionData, std::vector<uint16_t>& indicesData)
    {
        glGenVertexArrays(1, &m_vaoID);
        glGenBuffers(1, &m_vertexPositionBuffer);
        glGenBuffers(1, &m_indexBuffer);

        glBindVertexArray(m_vaoID);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indicesData.size(), indicesData.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionData.size(), positionData.data(), GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        // we assume that the vertex buffer contains only position data (3 floats per vertex)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);    
    }

    GeometryBuffer::~GeometryBuffer()
    {
        glDeleteBuffers(1, &m_indexBuffer);
        glDeleteBuffers(1, &m_vertexPositionBuffer);
        glDeleteVertexArrays(1, &m_vaoID);
    }

    void GeometryBuffer::Bind()
    {
        glBindVertexArray(m_vaoID);
    }

    void GeometryBuffer::Unbind()
    {
        glBindVertexArray(0);
    }
}