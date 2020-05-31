/*
===========================================================================
Renderable2D.h

Base class for all 2D renderable objects.
===========================================================================
*/

#pragma once

#include "Renderable.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Size2D.h"
#include "Graphics/Structures/Color.h"

namespace sedge
{
	class Renderer2D;
	class Texture2D;

	class Renderable2D : public Renderable
	{
	protected:
		Vector3 Position;
		Size2D Size;
		Color Col;
		Texture2D* Texture;

	protected:
		Renderable2D();
		Renderable2D(const Vector3& position, const Size2D& size, const Color& color);
		Renderable2D(const Vector3& position, const Size2D& size, Texture2D*const texture);

	public:
		virtual ~Renderable2D();

	public:
		inline virtual const Vector3& GetPosition() const { return Position; }
		inline const Size2D& GetSize() const { return Size; }
		inline const Color& GetColor() const { return Col; }
		virtual const ID GetTextureID() const;

		virtual void SetColor(const Color& color);
		virtual void SetPosition(const Vector2& position);
		virtual void SetZIndex(const float zIndex);

		virtual void Submit(Renderer2D*const renderer) const;
	};
}