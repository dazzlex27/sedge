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
		ElementBuffer(const uint count, uint*const dataPtr = nullptr, const DrawingMode drawingMode = Static);
		~ElementBuffer();

		void Map();
		void Unmap();

		void Bind() const override;
		void Unbind() const override;
	};
}