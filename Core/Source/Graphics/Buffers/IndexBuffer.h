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
			uint _bufferID;
			uint _count;

		public:
			IndexBuffer(uint* data, uint count);
			~IndexBuffer();

			inline const uint GetCount() const { return _count; }

			void Bind();
			void Unbind();
		};
	}
}