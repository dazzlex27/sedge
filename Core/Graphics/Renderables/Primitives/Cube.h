#pragma once

#include <CustomTypes.h>
#include "Graphics/Renderables/Renderable3D.h"

namespace sedge
{
	class VertexBuffer;
	class IndexBuffer;

	class Cube : public Renderable3D
	{
	public:
		Cube();
		Cube(const uint color);
		~Cube();

	private:
		void GenerateCube(const uint color);
	};
}