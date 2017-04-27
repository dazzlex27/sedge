#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	struct Point3D;
	struct Size3D;

	namespace graphics
	{
		class Mesh;
		class VertexBuffer;
		class IndexBuffer;
		class Texture2D;
		struct Color;

		class MeshFactory
		{
		public:
			static Mesh* CreateMesh(VertexBuffer* vbo, IndexBuffer* ibo);

			static Mesh* CreateCuboid(const Size3D& size, Texture2D* texture);
			static Mesh* CreateCuboid(const Size3D& size, const Color& color);

			static Mesh* CreateCube(float size, Texture2D* texture);
			static Mesh* CreateCube(float size, const Color& color);
		};
	}
}