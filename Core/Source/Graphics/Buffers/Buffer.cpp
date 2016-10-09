#include "Buffer.h"

namespace s3dge
{
	namespace Graphics
	{
		Buffer::Buffer(float* data, int count, uint componentCount)
			: m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void Buffer::Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void Buffer::Unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}