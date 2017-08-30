#pragma once

#include "Graphics/Buffers/BufferEnums.h"

namespace s3dge
{
	class RenderEnumParser
	{
	public:
		static int GetDrawingModeValue(const DrawingMode drawingMode);
		static int GetBufferTarget(const BufferTarget target);
	};

}