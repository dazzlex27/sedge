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
	class Renderer2D;
	class Texture2D;

	class Renderable2D
	{
	protected:
		Point3D Position;
		Size2D Size;
		Color Col;
		std::vector<Point2D> Uv;
		Texture2D* Texture;

	protected:
		Renderable2D();
		Renderable2D(const Point3D& position, const Size2D& size, const Color& color);
		Renderable2D(const Point3D& position, const Size2D& size, Texture2D* texture);

	public:
		virtual ~Renderable2D();
		virtual void Submit(Renderer2D* renderer) const;

	public:
		inline virtual const Point3D& GetPosition() const { return Position; }
		inline const Size2D& GetSize() const { return Size; }
		inline const Color& GetColor() const { return Col; }
		inline std::vector<Point2D> GetUV() const { return Uv; }
		inline id GetTextureID() const { return Texture ? Texture->GetID() : 0; }

		void SetColor(const Color& color);
		void SetPosition(const Point3D& position);
		void SetZIndex(float zIndex);

	private:
		void SetDefaultUVConfiguration();
	};
}