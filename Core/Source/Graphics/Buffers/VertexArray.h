/*
===========================================================================
VertexArray.h

Designed to store vertex positions before feeding them to OpenGL.
===========================================================================
*/

#pragma once

#include <vector>
#include "CustomTypes.h"

namespace s3dge
{
	class VertexBuffer;

	class VertexArray
	{
	private:
		uint _vertexArrayID;
		std::vector<VertexBuffer*> _buffers;

	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(VertexBuffer* buffer);
		void Bind() const;
		void Unbind() const;
		void Draw(uint indicesCount);
	};
}