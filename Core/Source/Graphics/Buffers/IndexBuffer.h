#pragma once

#include <GL/glew.h>
#include "S3DGETypes.h"

namespace S3DGE
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