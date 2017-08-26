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
		static Mesh*const CreateMesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, id*const textures = nullptr, const uint textureCount = 0);
		static Mesh*const CreateCubeOfUnitSize(Texture2D*const texture);
	};
}