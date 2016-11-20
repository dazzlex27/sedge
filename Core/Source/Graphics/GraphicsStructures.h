#pragma once

#include "S3DGETypes.h"
#include "Maths/MathsHeader.h"

namespace s3dge
{
	struct VertexData
	{
		Maths::vec3f Vertex;
		uint Color;
		Maths::vec2f UV;
		float TextureID;
	};
}