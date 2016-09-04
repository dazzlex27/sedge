#include "VertexArray.h"

namespace S3DGE
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
		}

		void VertexArray::AddBuffer(Buffer* buffer, uint index)
		{
			Bind();

			buffer->Bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			buffer->Unbind();

			Unbind();
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