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
			cstring text;
			Maths::vec2f position;

			Label(cstring text, float x, float y, float width, float height, uint color);
			~Label();
		};
	}
}