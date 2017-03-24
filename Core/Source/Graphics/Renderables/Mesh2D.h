#pragma once

#include <vector>

#include "Graphics/VertexData.h"
#include "Graphics/Structures/Color.h"

namespace s3dge
{
	namespace graphics
	{
		class Texture2D;
		struct VertexData;

		class Mesh2D
		{
		private:
			std::vector<VertexData> _vertices;
			std::vector<float> _indices;
			Color _color;

		public:
			Mesh2D(const std::vector<VertexData>& vertices, const std::vector<float> indices, const Color& color = Color(0xffffffff));

		public:
			const std::vector<VertexData>& GetVertices() const { return _vertices; }
			const std::vector<float>& GetIndices() { return _indices; }
			const Color& GetColor() const { return _color; }
		};
	}
}