#include "VertexArray.h"

namespace s3dge
{
	namespace Graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_VertexArrayID);
		}

		VertexArray::~VertexArray()
		{
			for (Buffer* item : m_Bufers)
				SafeDelete(item);

			glDeleteVertexArrays(1, &m_VertexArrayID);
		}

		void VertexArray::AddBuffer(Buffer* buffer, uint index)
		{
			glBindVertexArray(m_VertexArrayID);

			buffer->Bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			buffer->Unbind();

			glBindVertexArray(0);
		}

		void VertexArray::Bind() const
		{
			glBindVertexArray(m_VertexArrayID);
		}

		void VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}
	}
}