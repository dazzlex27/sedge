/*
===========================================================================
Color.h

A structure to represent color across the engine's graphics subsystem.
Uses uint internally to store the actual color value.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Math/Vector4.h"
#include "Utilities/Converters.h"

namespace s3dge
{
	namespace graphics
	{
		struct Color
		{
			uint value;

			Color(uint value) : value(value) { }
			Color(const math::vec4f& value) : value(ConvertColorToUint(value)) { }
			~Color() { }

			const math::vec4f& GetValueVec4() const { return ConvertColorToVec4(value); }
		};
	}
}