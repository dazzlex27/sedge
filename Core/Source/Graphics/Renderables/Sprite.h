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
			Sprite(float x, float y, float width, float height, Maths::vec4f color);
			Sprite(float x, float y, float width, float height, Texture* texture);
		};
	}
}