#pragma once

#include "Renderable2D.h"
#include "Graphics/Texture.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Sprite : public Renderable2D
		{
		public:
			Sprite(int x, int y, int width, int height, Maths::vec4f color);
			Sprite(int x, int y, int width, int height, Texture* texture);
		};
	}
}