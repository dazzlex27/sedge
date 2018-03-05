#pragma once

#include "CustomTypes.h"
#include "Graphics/Renderables/Renderable3D.h"

namespace s3dge
{
	class VertexBuffer;
	class IndexBuffer;

	class Cube : public Renderable3D
	{
	private:
		VertexBuffer* _vbo;
		IndexBuffer* _ibo;

	public:
		Cube();
		Cube(const uint color);
		~Cube();

		virtual void Draw() const override;

	private:
		void GenerateCube(const uint color);
	};
}