#pragma once

#include <vector>
#include <GL/glew.h>
#include "CustomTypes.h"
#include "Buffer.h"
#include "../../Internal/DeleteMacros.h"

namespace s3dge
{
	namespace Graphics
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