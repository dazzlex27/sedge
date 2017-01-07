/*
===========================================================================
IndexBuffer.h

Represents an entity called index buffer, designed to reduce the number of vertices in a mesh.
===========================================================================
*/

#pragma once

#include <GL/glew.h>
#include "CustomTypes.h"

namespace s3dge
{
	namespace graphics
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