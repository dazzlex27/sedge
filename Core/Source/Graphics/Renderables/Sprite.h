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

		private:
			Sprite(const Point2D& position, float zIndex, const Size2D& size, const Color& color);
			Sprite(const Point2D& position, float zIndex, const Size2D& size, Texture2D* texture);

		public:
			inline const Point3D& GetPosition() const override { return position; }

			friend class SpriteFactory;
		};
	}
}