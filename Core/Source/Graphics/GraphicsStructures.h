/*
===========================================================================
GraphicsStructures.h

This file contains the necessary structures used by the Graphics namespace
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Maths/MathsHeader.h"

namespace s3dge
{
	struct VertexData
	{
		maths::vec3f Vertex;
		uint Color;
		maths::vec2f UV;
		float TextureID;
	};
}