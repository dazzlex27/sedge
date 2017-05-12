/*
===========================================================================
Renderable2D.h

Base class for all 2D renderable objects.
===========================================================================
*/

#pragma once

#include <vector>
#include "Renderable.h"
#include "Graphics/Structures/Color.h"
#include "Math/Point2D.h"
#include "Math/Point3D.h"
#include "Math/Size2D.h"
#include "Graphics/Textures/Texture2D.h"

namespace s3dge
{
	namespace graphics
	{
		class Renderer2D;
		class Texture2D;

		class Renderable2D
		{
		protected:
			Point3D _position;
			Size2D _size;
			Color _color;
			std::vector<Point2D> _uv;
			Texture2D* _texture;

		protected:
			Renderable2D();
			Renderable2D(const Point3D& position, const Size2D& size, const Color& color);
			Renderable2D(const Point3D& position, const Size2D& size, Texture2D* texture);

		public:
			virtual ~Renderable2D();
			virtual void Submit(Renderer2D* renderer) const;

		public:
			inline virtual const Point3D& GetPosition() const { return _position; }
			inline const Size2D& GetSize() const { return _size; }
			inline const Color& GetColor() const { return _color; }
			inline std::vector<Point2D> GetUV() const { return _uv; }
			inline id GetTextureID() const { return _texture ? _texture->GetID() : 0; }

			void SetColor(const Color& color);
			void SetPosition(const Point3D& position);

		private:
			void SetDefaultUVConfiguration();
		};
	}
}