/*
===========================================================================
ElementBuffer.h

Represents an entity called element buffer, designed to reduce the number of vertices in a mesh.
===========================================================================
*/

#pragma once

#include "Buffer.h"

namespace s3dge
{
	class ElementBuffer : public Buffer
	{
	public:
		ElementBuffer(uint count, uint* dataPtr = nullptr, DrawingMode drawingMode = STATIC_DRAW);
		~ElementBuffer();

		void Bind() const override;
		void Unbind() const override;
	};
}