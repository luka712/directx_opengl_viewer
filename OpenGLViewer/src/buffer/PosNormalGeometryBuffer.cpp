#include "buffer/PosNormalGeometryBuffer.hpp"
#include <glad/glad.h>

namespace Viewer
{
	void PosNormalGeometryBuffer::Initialize(
		std::vector<float> &positionData,
		std::vector<uint16_t> &indicesData,
		std::vector<float> &normalData)
	{
		m_indexCount = indicesData.size();
		m_verticesCount = positionData.size() / 3;

		glGenVertexArrays(1, &m_vaoID);

		glBindVertexArray(m_vaoID);

		if (indicesData.size() > 0)
		{
			// Indices
			glGenBuffers(1, &m_indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indicesData.size(), indicesData.data(), GL_STATIC_DRAW);
		}

		// Position(xyz)
		glGenBuffers(1, &m_vertexPositionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionData.size(), positionData.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if (normalData.size() > 0)
		{
			// Normals(xyz)
			glGenBuffers(1, &m_vertexNormalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexNormalBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalData.size(), normalData.data(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glBindVertexArray(0);
	}

	PosNormalGeometryBuffer::~PosNormalGeometryBuffer()
	{
		glDeleteBuffers(1, &m_indexBuffer);
		glDeleteBuffers(1, &m_vertexPositionBuffer);
		glDeleteBuffers(1, &m_vertexNormalBuffer);
		glDeleteVertexArrays(1, &m_vaoID);
	}

	void PosNormalGeometryBuffer::Bind()
	{
		glBindVertexArray(m_vaoID);
	}

	void PosNormalGeometryBuffer::Unbind()
	{
		glBindVertexArray(0);
	}

	void PosNormalGeometryBuffer::Draw()
	{
		Bind();

		if (m_indexCount > 0)
		{
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_verticesCount);
		}
		Unbind();
	}
}