/*
===========================================================================
VertexBuffer.h

A class desinged to manage an OpenGL buffer for creating vertex buffers.
===========================================================================
*/

#pragma once

#include "Buffer.h"

namespace s3dge
{
	class VertexLayout;

	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(int elementSize, uint elementCount, void* dataPtr = nullptr, DrawingMode drawingMode = STATIC_DRAW);
		~VertexBuffer();

		void SetLayout(VertexLayout* layout);

		void Bind() const override;
		void Unbind() const override;

		void Map();
		void Unmap();
	};
}