/*
===========================================================================
IndexBuffer.h

Represents an entity called index buffer, designed to reduce the number of vertices in a mesh.
===========================================================================
*/

#pragma once

#include "Buffer.h"

namespace s3dge
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const uint count, uint*const dataPtr = nullptr, const DrawingMode drawingMode = Static);
	};
}