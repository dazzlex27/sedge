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
	private:
		VertexLayout* _layout;

	public:
		VertexBuffer(uint vertexSize, uint vertexCount, const VertexLayout& layout, void*const dataPtr = nullptr, DrawingMode drawingMode = Static);
		virtual ~VertexBuffer();

		virtual void Bind() const override;

	private:
		void BindLayout() const;
	};
}