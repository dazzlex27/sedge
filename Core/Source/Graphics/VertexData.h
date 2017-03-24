/*
===========================================================================
VertexData.h

This file contains the necessary structures used by the Graphics namespace
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Graphics/Structures/Color.h"
#include "Graphics/Structures/Point2D.h"
#include "Graphics/Structures/Point3D.h"

namespace s3dge
{
	namespace graphics
	{
		struct VertexData
		{
			Point3D Vertex;
			Color Color;
			Point2D UV;
			float TextureID;
		};
	}
}