/*
===========================================================================
GraphicsStructures.h

This file contains the necessary structures used by the Graphics namespace
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace s3dge
{
	namespace graphics
	{
		struct VertexData
		{
			math::vec3f Vertex;
			uint Color;
			math::vec2f UV;
			float TextureID;
		};
	}
}