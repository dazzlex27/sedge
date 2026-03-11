#include "FrameBuffer.h"
#include "Graphics/GraphicsAPI.h"

using namespace sedge;

FrameBuffer::FrameBuffer()
{
	GraphicsAPI::GenFramebuffers(1, &_bufferID);
}

FrameBuffer::~FrameBuffer()
{
	GraphicsAPI::DeleteFramebuffers(1, &_bufferID);
}

void FrameBuffer::Bind() const
{
	GraphicsAPI::BindFramebuffer(_bufferID);
}

void FrameBuffer::Unbind() const
{
	GraphicsAPI::BindFramebuffer(0);
}

const bool FrameBuffer::IsComplete() const
{
	return GraphicsAPI::IsFramebufferComplete(_bufferID);
}

void FrameBuffer::AttachColor(const ID texture)
{
}

void FrameBuffer::AttachDepth(const ID texture)
{
}

void FrameBuffer::AttachStencil(const ID texture)
{
}
