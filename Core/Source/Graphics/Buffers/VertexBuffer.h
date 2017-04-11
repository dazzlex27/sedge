/*
===========================================================================
VertexBuffer.h

A class desinged to manage an OpenGL buffer for creating vertex buffers.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	namespace graphics
	{
		class VertexLayout;

		class VertexBuffer
		{
		private:
			uint _bufferID;
			uint _componentCount;
			void* _data;

		public:
			VertexBuffer(void* data, int componentSize, uint componentCount);
			VertexBuffer(int componentSize, uint componentCount);
			~VertexBuffer();

			inline const uint GetComponentCount() const { return _componentCount; }
			void* GetDataPointer() { return _data; }
			void SetLayout(VertexLayout* layout);

			inline void Bind() const;
			inline void Unbind() const;
			void Map();
			void Unmap();
		};
	}
}