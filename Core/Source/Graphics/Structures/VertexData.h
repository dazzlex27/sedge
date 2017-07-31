/*
===========================================================================
VertexData.h

This file contains the necessary VertexData structures used by the Graphics namespace
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Graphics/Structures/Color.h"
#include "Math/Point2D.h"
#include "Math/Point3D.h"

namespace s3dge
{
	struct VertexData
	{
		Point3D Position;
		Color Color;
		Vector3 Normal;
		Point2D UV;
		float TextureID;
	};
}