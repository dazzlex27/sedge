#pragma once

#include "S3DGETypes.h"
#include "Renderable2D.h"

namespace s3dge
{
	namespace Graphics
	{
		class Label : public Renderable2D
		{
		public:
			std::string text;
			Maths::vec2f position;
			uint color;

			Label(const std::string& text, float x, float y, float width, float height, uint color);
			~Label();

			void Submit(Renderer2DBase* renderer) const override;
		};
	}
}