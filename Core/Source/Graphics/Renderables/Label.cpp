#include "Label.h"

namespace s3dge
{
	namespace Graphics
	{
		Label::Label(const std::string& text, float x, float y, float width, float height, uint color)
			: Renderable2D(Maths::vec3f(x,y,0),Maths::vec2f(width, height), color)
		{
			this->text = text;
			this->position = Maths::vec2f(x, y);
			this->color = _color;
		}

		Label::~Label()
		{

		}

		void Label::Submit(Renderer2DBase* renderer) const
		{
			renderer->DrawString(text, Maths::vec3f(position.x, position.y, 0), color);
		}
	}
}


