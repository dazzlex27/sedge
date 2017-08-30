#include "RenderEnumParser.h"

#include <GL/glew.h>

using namespace s3dge;

int RenderEnumParser::GetDrawingModeValue(const DrawingMode drawingMode)
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

int RenderEnumParser::GetBufferTarget(const BufferTarget target)
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
