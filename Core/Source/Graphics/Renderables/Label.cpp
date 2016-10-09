#include "Label.h"

namespace s3dge
{
	namespace Graphics
	{
		Label::Label(cstring text, float x, float y, float width, float height, uint color)
			: Renderable2D(Maths::vec3f(x,y,0),Maths::vec2f(width, height), color)
		{
			this->text = text;
			this->position = Maths::vec2f(x, y);
		}

		Label::~Label()
		{

		}
	}
}


