/*
===========================================================================
OpenGLBindings.h

Implements GraphicsAPI functions for OpenGL.
This should be the only place where GL/glew.h is included!
===========================================================================
*/

#pragma once

#include "GraphicsAPI.h"
#include "GraphicsAPIEnumConverter.h"
#include <GL/glew.h>

using namespace s3dge;

typedef GraphicsAPIEnumConverter EnumConverter;

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
	glBindBuffer(EnumConverter::GetBufferTarget(target), id);
}

void GraphicsAPI::SetBufferData(const BufferTarget target, const uint bufferSize, const void* bufferData, const DrawingMode hint)
{
	glBufferData(EnumConverter::GetBufferTarget(target), bufferSize, bufferData, EnumConverter::GetDrawingModeValue(hint));
}

void* GraphicsAPI::MapBufferForWriting(const BufferTarget target)
{
	return glMapBuffer(EnumConverter::GetBufferTarget(target), GL_WRITE_ONLY);
}

void GraphicsAPI::UnmapBuffer(const BufferTarget target)
{
	glUnmapBuffer(EnumConverter::GetBufferTarget(target));
}

void GraphicsAPI::GenVertexArrays(const uint n, uint* const arrays)
{
	glGenVertexArrays(n, arrays);
}

void GraphicsAPI::DeleteVertexArrays(const uint n, uint*const arrays)
{
	glDeleteVertexArrays(1, arrays);
}

void GraphicsAPI::BindVertexArray(const uint id)
{
	glBindVertexArray(id);
}

void GraphicsAPI::EnableVertexAttributeArray(const uint index)
{
	glEnableVertexAttribArray(index);
}

void GraphicsAPI::VertexAttributePointer(const uint index, const int size, const int type, const int normalized, const int stride, const void * const offset)
{
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void GraphicsAPI::DrawArrays(const PrimitiveType primitiveType, const int first, const uint count)
{
	glDrawArrays(EnumConverter::GetPrimitiveType(primitiveType), first, count);
}

void GraphicsAPI::DrawElements(const PrimitiveType primitiveType, const uint count, const ValueType type, const void*const elements)
{
	glDrawElements(EnumConverter::GetPrimitiveType(primitiveType), count, EnumConverter::GetValueType(type), elements);
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
	glBindTexture(EnumConverter::GetTextureTarget(target), id);
}

void GraphicsAPI::GenerateMipmap(const TextureTarget target)
{
	glGenerateMipmap(EnumConverter::GetTextureTarget(target));
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

// ============================================================================
// Enum converters
// ============================================================================

const int EnumConverter::GetDrawingModeValue(const DrawingMode drawingMode)
{
	switch (drawingMode)
	{
	case Dynamic:
		return GL_DYNAMIC_DRAW;
	case Static:
		return GL_STATIC_DRAW;
	case Stream:
		return GL_STREAM_DRAW;
	default:
		return 0;
	}
}

const int EnumConverter::GetBufferTarget(const BufferTarget target)
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

const int EnumConverter::GetTextureTarget(const TextureTarget target)
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

const int EnumConverter::GetPrimitiveType(const PrimitiveType type)
{
	switch (type)
	{
	case Triangles:
		return GL_TRIANGLES;
	case Lines:
		return GL_LINES;
	case Points:
		return GL_POINTS;
	case LineStrips:
		return GL_LINE_STRIP;
	case Quads:
		return GL_QUADS;
	case LineLoops:
		return GL_LINE_LOOP;
	case QuadStrips:
		return GL_QUAD_STRIP;
	case Polygons:
		return GL_POLYGON;
	default:
		return 0;
	}
}

const int EnumConverter::GetValueType(const ValueType type)
{
	switch (type)
	{
	case UnsginedShort:
		return GL_UNSIGNED_SHORT;
	case UnsignedInt:
		return GL_UNSIGNED_INT;
	default:
		return 0;
	}
}
