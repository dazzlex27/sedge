/*
===========================================================================
Buffer.cpp

Implements Buffer class.
===========================================================================
*/

#include "Buffer.h"
#include "Graphics/GraphicsAPI.h"

using namespace sedge;

Buffer::Buffer(const BufferTarget target, const uint elementSize, const uint elementCount, void*const dataPtr, const DrawingMode drawingMode)
	: Target(target), ElementSize(elementSize), ElementCount(elementCount), DataPtr(dataPtr), Mode(drawingMode)
{
	GraphicsAPI::GenBuffers(1, &BufferID);
	Bind();
	GraphicsAPI::SetBufferData(Target, ElementSize * ElementCount, DataPtr, drawingMode);
	Unbind();
}

Buffer::~Buffer()
{
	GraphicsAPI::DeleteBuffers(1, &BufferID);
}

void Buffer::Bind() const
{
	GraphicsAPI::BindBuffer(Target, BufferID);
}

void Buffer::Unbind() const
{
	GraphicsAPI::BindBuffer(Target, 0);
}

void Buffer::Map()
{
	DataPtr = GraphicsAPI::MapBufferForWriting(Target);
}

void Buffer::Unmap()
{
	GraphicsAPI::UnmapBuffer(Target);
}
