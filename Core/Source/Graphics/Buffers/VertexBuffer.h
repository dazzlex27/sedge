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
		VertexBuffer(uint vertexSize, uint vertexCount, void*const dataPtr = nullptr, DrawingMode drawingMode = Static);
	};
}