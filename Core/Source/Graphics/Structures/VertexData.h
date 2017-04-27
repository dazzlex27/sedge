/*
===========================================================================
VertexData.h

This file contains the necessary VertexData structures used by the Graphics namespace
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Graphics/Structures/Color.h"
#include "Common/Structures/Point2D.h"
#include "Common/Structures/Point3D.h"

namespace s3dge
{
	namespace graphics
	{
		struct VertexData
		{
			Point3D Position;
			Color Color;
			Point2D UV;
			float TextureID;
		};
	}
}