#pragma once

#include <GL/glew.h>
#include "CustomTypes.h"

namespace s3dge
{
	namespace Graphics
	{
		class IndexBuffer
		{
		private:
			uint m_BufferID;
			uint m_Count;

		public:
			IndexBuffer(uint* data, uint count);
			~IndexBuffer();

			inline const uint GetCount() const { return m_Count; }

			void Bind();
			void Unbind();
		};
	}
}