/*
===========================================================================
Renderable2D.h

Base class for all 2D renderable objects.
===========================================================================
*/

#pragma once

#include "Renderable.h"
#include "Math/Point2D.h"
#include "Math/Point3D.h"
#include "Math/Size2D.h"
#include "Graphics/Structures/Color.h"

namespace s3dge
{
	class Texture2D;

	class Renderable2D : public Renderable
	{
	protected:
		Point3D Position;
		Size2D Size;
		Color Col;

	protected:
		Renderable2D();
		Renderable2D(const Point3D& position, const Size2D& size, const Color& color);
		Renderable2D(const Point3D& position, const Size2D& size, Texture2D* texture);

	public:
		virtual ~Renderable2D();

	public:
		inline virtual const Point3D& GetPosition() const { return Position; }
		inline const Size2D& GetSize() const { return Size; }
		inline const Color& GetColor() const { return Col; }

		virtual void SetColor(const Color& color);
		virtual void SetPosition(const Point2D& position);
		virtual void SetZIndex(float zIndex);

	private:
		void PerformDefaultGeometrySetup();
	};
}