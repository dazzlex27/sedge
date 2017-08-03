#pragma once

#include "CustomTypes.h"
#include "Graphics/Buffers/Buffer.h"

namespace s3dge
{
	struct Size3D;

	class Mesh;
	struct VertexData;
	class VertexBuffer;
	class ElementBuffer;
	class Texture2D;
	struct Color;

	class MeshFactory
	{
	public:
		static Mesh*const CreateMesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, Texture2D*const texture = nullptr);

		static Mesh*const CreateCuboid(const Size3D& size, Texture2D*const texture, const DrawingMode drawingMode);
		static Mesh*const CreateCuboid(const Size3D& size, const Color& color, const DrawingMode drawingMode);

		static Mesh*const CreateCube(const float size, Texture2D*const texture, const DrawingMode drawingMode);
		static Mesh*const CreateCube(const float size, const Color& color, const DrawingMode drawingMode);
	};
}