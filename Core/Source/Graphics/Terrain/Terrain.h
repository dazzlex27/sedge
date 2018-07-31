#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	class VertexBuffer;
	class IndexBuffer;
	class Texture2D;

	class Terrain
	{
	private:
		VertexBuffer* _vbo;
		IndexBuffer* _ibo;
		Texture2D*const _texture;

	public:
		Terrain(Texture2D*const texture);
		~Terrain();

		void Draw() const;

	private:
		void GenerateTerrain();
	};
}