/*
===========================================================================
GraphicsAPIEnumParser.h

Declares parsers to convert s3dge graphics enums to API-dependent ones.
===========================================================================
*/

#pragma once

#include "Graphics/Buffers/BufferEnums.h"
#include "Graphics/Textures/TextureEnums.h"

namespace s3dge
{
	class GraphicsAPIEnumParser
	{
	public:
		static int GetDrawingModeValue(const DrawingMode drawingMode);
		static int GetBufferTarget(const BufferTarget target);

		static int GetTextureTarget(const TextureTarget target);
	};
}