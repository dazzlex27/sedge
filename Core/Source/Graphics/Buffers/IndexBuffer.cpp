#include "IndexBuffer.h"

namespace s3dge
{
	namespace Graphics
	{
		IndexBuffer::IndexBuffer(uint* data, uint count)
			: m_Count(count)
		{
			glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IndexBuffer::Unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}