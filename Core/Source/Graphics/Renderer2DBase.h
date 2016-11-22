#pragma once

#include <string>
#include "CustomTypes.h"
#include "Maths/MathsHeader.h"
#include "Fonts/Font.h"

namespace s3dge
{
	namespace Graphics
	{
		class Renderable2D;

		class Renderer2DBase
		{
		public:
			virtual void Begin() = 0;
			virtual void Submit(const Renderable2D* renderable) = 0;
			virtual void Flush() = 0;
			virtual void End() = 0;

			virtual void DrawRectangle(const Maths::vec3f& position, const Maths::vec2f& size, uint color) {}
			virtual void DrawOval(const Maths::vec3f& position, int radiusX, int radiusY, uint color) {}
			virtual void DrawString(const std::string& text, Font* font, const Maths::vec3f& position, uint color) {}
		};
	}
}