#include "Buffer.h"
#include "Graphics/RenderSystem.h"

using namespace s3dge;

Buffer::Buffer(const BufferTarget target, const uint elementSize, const uint elementCount, void*const data, const DrawingMode drawingMode)
	: Target(target), ElementSize(elementSize), ElementCount(elementCount), DataPtr(data)
{
	RenderSystem::GenBuffers(1, &BufferID);
	RenderSystem::BindBuffer(Target, BufferID);
	RenderSystem::SetBufferData(Target, elementCount * sizeof(/* DEREFERENCE!! */data), data, drawingMode);
	RenderSystem::BindBuffer(Target, 0);
}

Buffer::~Buffer()
{
	RenderSystem::DeleteBuffers(1, &BufferID);
}

void Buffer::Bind() const
{
	RenderSystem::BindBuffer(Target, BufferID);
}

void Buffer::Unbind() const
{
	RenderSystem::BindBuffer(Target, 0);
}

void Buffer::Map()
{
	DataPtr = RenderSystem::MapBufferForWriting(Target);
}

void Buffer::Unmap()
{
	RenderSystem::UnmapBuffer(Target);
}