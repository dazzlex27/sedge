/*
===========================================================================
OpenGLBindings.h

Implements GraphicsAPI functions for OpenGL.
This should be the only place where GL/glew.h is included!
===========================================================================
*/

#pragma once

#include "GraphicsAPI.h"
#include "GraphicsAPIEnumParser.h"
#include <GL/glew.h>

using namespace s3dge;

void GraphicsAPI::GenBuffers(const uint n, uint*const buffers)
{
	glGenBuffers(n, buffers);
}

void GraphicsAPI::DeleteBuffers(const uint n, uint*const buffers)
{
	glDeleteBuffers(n, buffers);
}

void GraphicsAPI::BindBuffer(const BufferTarget target, const uint id)
{
	glBindBuffer(GraphicsAPIEnumParser::GetBufferTarget(target), id);
}

void GraphicsAPI::SetBufferData(const BufferTarget target, const uint bufferSize, const void* bufferData, const DrawingMode mode)
{
	glBufferData(GraphicsAPIEnumParser::GetBufferTarget(target), bufferSize, bufferData, GraphicsAPIEnumParser::GetDrawingModeValue(mode));
}

void* GraphicsAPI::MapBufferForWriting(const BufferTarget target)
{
	return glMapBuffer(GraphicsAPIEnumParser::GetBufferTarget(target), GL_WRITE_ONLY);
}

void GraphicsAPI::UnmapBuffer(const BufferTarget target)
{
	glUnmapBuffer(GraphicsAPIEnumParser::GetBufferTarget(target));
}

void GraphicsAPI::GenTextures(const uint n, uint*const textures)
{
	glGenTextures(n, textures);
}

void GraphicsAPI::DeleteTextures(const uint n, uint*const textures)
{
	glDeleteTextures(n, textures);
}

void GraphicsAPI::BindTexture(const TextureTarget target, const uint id)
{
	glBindTexture(GraphicsAPIEnumParser::GetTextureTarget(target), id);
}

void GraphicsAPI::GenerateMipmap(const TextureTarget target)
{
	glGenerateMipmap(GraphicsAPIEnumParser::GetTextureTarget(target));
}

void GraphicsAPI::ActivateTexture(const uint num)
{
	glActiveTexture(GL_TEXTURE0 + num);
}

void GraphicsAPI::EnableFaceCulling()
{
	glEnable(GL_CULL_FACE);
}

void GraphicsAPI::DisableFaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void GraphicsAPI::SetFaceCulling(const bool cullFaces)
{
	if (cullFaces)
		EnableFaceCulling();
	else
		DisableFaceCulling();
}

void GraphicsAPI::EnableDepthTesting()
{
	glEnable(GL_DEPTH_TEST);
}

void GraphicsAPI::DisableDepthTesting()
{
	glDisable(GL_DEPTH_TEST);
}

void GraphicsAPI::SetDepthTesting(const bool testDepth)
{
	if (testDepth)
		EnableDepthTesting();
	else
		DisableDepthTesting();
}

int GraphicsAPIEnumParser::GetDrawingModeValue(const DrawingMode drawingMode)
{
	switch (drawingMode)
	{
	case DrawingMode::Dynamic:
		return GL_DYNAMIC_DRAW;
	case DrawingMode::Static:
		return GL_STATIC_DRAW;
	case DrawingMode::Stream:
		return GL_STREAM_DRAW;
	default:
		return 0;
	}
}

int GraphicsAPIEnumParser::GetBufferTarget(const BufferTarget target)
{
	switch (target)
	{
	case Element:
		return GL_ELEMENT_ARRAY_BUFFER;
	case Array:
		return GL_ARRAY_BUFFER;
	default:
		return 0;
	}
}

int GraphicsAPIEnumParser::GetTextureTarget(const TextureTarget target)
{
	switch (target)
	{
	case Tex2D:
		return GL_TEXTURE_2D;
	case Cube:
		return GL_TEXTURE_CUBE_MAP;
	default:
		return 0;
	}
}
