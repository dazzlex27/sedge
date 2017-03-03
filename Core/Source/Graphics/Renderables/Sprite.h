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
			Point3D position;

		public:
			Sprite(float x, float y, float width, float height, const Color& color);
			Sprite(float x, float y, float width, float height, Texture2D* texture);

			inline const Point3D& GetPosition() const override { return position; }
		};
	}
}