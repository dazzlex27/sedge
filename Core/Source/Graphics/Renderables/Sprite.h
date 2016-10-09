#pragma once

#include "Renderable2D.h"

namespace s3dge
{
	namespace Graphics
	{
		class Sprite : public Renderable2D
		{
		public:
			Maths::vec3f position;

		public:
			Sprite(float x, float y, float width, float height, uint color);
			Sprite(float x, float y, float width, float height, Texture* texture);
		};
	}
}