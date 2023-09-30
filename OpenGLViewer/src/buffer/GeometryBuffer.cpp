#include "buffer/GeometryBuffer.hpp"
#include <glad/glad.h>

namespace Viewer
{
    void GeometryBuffer::Initialize(
    std::vector<float> &positionData, 
    std::vector<uint16_t> &indicesData, 
    std::vector<float> &textureCoords,
    std::vector<float> &normalData)
    {
        m_indexCount = indicesData.size();

        glGenVertexArrays(1, &m_vaoID);
        glGenBuffers(1, &m_vertexPositionBuffer);
        glGenBuffers(1, &m_vertexTextureBuffer);
        glGenBuffers(1, &m_indexBuffer);

        glBindVertexArray(m_vaoID);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indicesData.size(), indicesData.data(), GL_STATIC_DRAW);

        // Position(xyz)
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionData.size(), positionData.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Texture(uv)
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexTextureBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textureCoords.size(), textureCoords.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        // Normals(xyz)
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexNormalBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalData.size(), normalData.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);


        glBindVertexArray(0);
    }

    GeometryBuffer::~GeometryBuffer()
    {
        glDeleteBuffers(1, &m_indexBuffer);
        glDeleteBuffers(1, &m_vertexPositionBuffer);
        glDeleteBuffers(1, &m_vertexTextureBuffer);
        glDeleteBuffers(1, &m_vertexNormalBuffer);
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

    void GeometryBuffer::Draw()
    {
        Bind();
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);
        Unbind();
    }
}