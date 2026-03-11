#pragma once

#include <vector>
#include <CustomTypes.h>

namespace sedge
{
	class Mesh;
	class Texture2D;
	struct VertexData;

	class MeshFactory
	{
	public:
		static Mesh*const CreateMesh(const char*const name,
			std::vector<VertexData> vertices,
			std::vector<uint> elements,
			std::vector<Texture2D*> diffTextures = std::vector<Texture2D*>(),
			std::vector<Texture2D*> specTextures = std::vector<Texture2D*>());
	};
}