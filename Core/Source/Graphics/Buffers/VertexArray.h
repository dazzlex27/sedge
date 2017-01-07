/*
===========================================================================
VertexArray.h

Designed to store vertex positions before feeding them to OpenGL.
===========================================================================
*/

#pragma once

#include <vector>
#include <GL/glew.h>
#include "CustomTypes.h"
#include "Buffer.h"

namespace s3dge
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			uint _vertexArrayID;
			std::vector<Buffer*> _buffers;

		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer* buffer, uint index);
			void Bind() const;
			void Unbind() const;
		};
	}
}