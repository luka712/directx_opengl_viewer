#ifndef UNIFORM_BUFFER_HPP

#define UNIFORM_BUFFER_HPP

#include <glad/glad.h>

namespace Viewer
{
	template <typename T>
	class UniformBuffer
	{
	public:

		// @brief Initialize the uniform buffer.
		// @param length - The length of the data. Multiplied by sizeof(T)
		// @return True if the buffer was initialized successfully, false otherwise.
		bool Initialize(int length = 1)
		{
			return	Initialize(nullptr, length);
		}

		/**
		 * @brief Initialize the uniform buffer.
		 * @param data - The data to be stored in the buffer.
		 * @param length - The length of the data.
		 * @return True if the buffer was initialized successfully, false otherwise.
		*/
		bool Initialize(T* data, int length = 1)
		{
			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
			size_t byteSize = sizeof(T) * length;
			glBufferData(GL_UNIFORM_BUFFER, byteSize, data, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

			return true;
		}

		void Update(T* data, int length = 1)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T) * length, data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		inline GLuint GetBufferID() const
		{
			return m_bufferID;
		}

	private:
		GLuint m_bufferID;
	};
}

#endif