/*
===========================================================================
Sprite.h

Inherits from the Renderable2D.
===========================================================================
*/

#pragma once

#include "Renderable2D.h"

namespace s3dge
{
	namespace graphics
	{
		class Sprite : public Renderable2D
		{
		public:
			math::vec3f position;

		public:
			Sprite(float x, float y, float width, float height, uint color);
			Sprite(float x, float y, float width, float height, Texture2D* texture);

			inline const math::vec3f GetPosition() const override { return position; }
		};
	}
}