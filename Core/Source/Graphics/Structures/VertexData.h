/*
===========================================================================
VertexData.h

This file contains the necessary VertexData structures used by the Graphics namespace
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Graphics/Structures/Color.h"

namespace s3dge
{
	struct VertexData
	{
		Vector3 Position;
		Color Color;
		Vector3 Normal;
		Vector2 UV;
		float TextureID;
	};

	struct VertexDataS
	{
		Vector3 Position;
		Color Color;
		Vector2 UV;
		float TextureID;
	};
}