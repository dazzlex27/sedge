#include "Buffer.h"
#include "Graphics/GraphicsAPI.h"

using namespace s3dge;

Buffer::Buffer(const BufferTarget target, const uint elementSize, const uint elementCount, void*const data, const DrawingMode drawingMode)
	: Target(target), ElementSize(elementSize), ElementCount(elementCount), DataPtr(data)
{
	GraphicsAPI::GenBuffers(1, &BufferID);
	GraphicsAPI::BindBuffer(Target, BufferID);
	GraphicsAPI::SetBufferData(Target, elementCount * sizeof(/* DEREFERENCE!! */data), data, drawingMode);
	GraphicsAPI::BindBuffer(Target, 0);
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