#pragma once

#include <GL/glew.h>
#include "S3DGETypes.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Buffer
		{
		private:
			uint m_BufferID;
			uint m_ComponentCount;

		public:
			Buffer(float* data, int count, uint componentCount);
			~Buffer();

			inline const uint GetComponentCount() const { return m_ComponentCount; }

			void Bind();
			void Unbind();
		};
	}
}