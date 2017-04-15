/*
===========================================================================
Color.h

A structure to represent color across the engine's graphics subsystem.
Uses uint internally to store the actual RGB-color value.
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

			Color() : value(0) { }
			Color(uint value) : value(value) { }
			Color(const math::Vector4& value) : value(ConvertColorToUint(value)) { }
			~Color() { }

			const math::Vector4& GetValueVec4() const { return ConvertColorToVec4(value); }
		};
	}
}