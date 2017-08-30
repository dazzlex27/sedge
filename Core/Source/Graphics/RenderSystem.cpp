#include "RenderSystem.h"
#include "RenderEnumParser.h"
#include <GL/glew.h>

using namespace s3dge;

void RenderSystem::GenBuffers(const uint n, uint*const buffers)
{
	glGenBuffers(n, buffers);
}

void RenderSystem::DeleteBuffers(const uint n, uint*const buffers)
{
	glDeleteBuffers(n, buffers);
}

void RenderSystem::BindBuffer(const BufferTarget target, const uint id)
{
	// TODO
	glBindBuffer(target, id);
}

void RenderSystem::SetBufferData(const BufferTarget target, const uint bufferSize, const void* bufferData, const DrawingMode mode)
{
	glBufferData(RenderEnumParser::GetBufferTarget(target), bufferSize, bufferData, RenderEnumParser::GetDrawingModeValue(mode));
}

void* RenderSystem::MapBufferForWriting(const BufferTarget target)
{
	return glMapBuffer(RenderEnumParser::GetBufferTarget(target), GL_WRITE_ONLY);
}

void RenderSystem::UnmapBuffer(const BufferTarget target)
{
	glUnmapBuffer(RenderEnumParser::GetBufferTarget(target));
}

void RenderSystem::GenTextures(const uint n, uint*const textures)
{
	glGenTextures(n, textures);
}

void RenderSystem::DeleteTextures(const uint n, uint*const textures)
{
	glDeleteTextures(n, textures);
}

void RenderSystem::BindTexture(const TextureTarget target, const uint id)
{
	// TODO
	glBindTexture(target, id);
}

void RenderSystem::GenerateMipmap(const TextureTarget target)
{
	// TODO;
	glGenerateMipmap(target);
}

void RenderSystem::EnableFaceCulling()
{
	glEnable(GL_CULL_FACE);
}

void RenderSystem::DisableFaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void RenderSystem::SetFaceCulling(const bool cullFaces)
{
	if (cullFaces)
		EnableFaceCulling();
	else
		DisableFaceCulling();
}

void RenderSystem::EnableDepthTesting()
{
	glEnable(GL_DEPTH_TEST);
}

void RenderSystem::DisableDepthTesting()
{
	glDisable(GL_DEPTH_TEST);
}

void RenderSystem::SetDepthTesting(const bool testDepth)
{
	if (testDepth)
		EnableDepthTesting();
	else
		DisableDepthTesting();
}