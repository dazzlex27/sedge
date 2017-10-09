#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	class Mesh;
	class Texture2D;
	struct VertexData;

	class MeshFactory
	{
	public:
		static Mesh*const CreateMesh(
			VertexData*const vertices, const uint vertexCount, 
			uint*const elements, const uint elementCount, 
			ID*const diffTextures = nullptr, const uint diffTexCount = 0,
			ID*const specTextures = nullptr, const uint specTexCount = 0);
		static Mesh*const CreateCubeOfUnitSize(Texture2D*const texture);
	};
}