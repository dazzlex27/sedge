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
		VertexBuffer(const uint vertexSize, const uint vertexCount, void*const data = nullptr, const DrawingMode drawingMode = Static);
	};
}