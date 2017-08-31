/*
===========================================================================
GraphicsAPIEnumParser.h

Declares parsers to convert s3dge graphics enums to API-dependent ones.
===========================================================================
*/

#pragma once

#include "Graphics/Buffers/BufferEnums.h"
#include "Graphics/Textures/TextureEnums.h"
#include "DrawingEnums.h"

namespace s3dge
{
	class GraphicsAPIEnumConverter
	{
	public:
		static const int GetDrawingModeValue(const DrawingMode drawingMode);
		static const int GetBufferTarget(const BufferTarget target);

		static const int GetTextureTarget(const TextureTarget target);

		static const int GetPrimitiveType(const PrimitiveType type);
		static const int GetValueType(const ValueType type);
	};
}