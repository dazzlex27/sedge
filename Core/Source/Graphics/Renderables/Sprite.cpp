#include "Sprite.h"

namespace s3dge
{
	namespace Graphics
	{
		Sprite::Sprite(float x, float y, float width, float height, uint color)
			: Renderable2D(Maths::vec3f(x, y, 0), Maths::vec2f(width, height), color)
		{
			this->position = m_Position;
		}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(Maths::vec3f(x, y, 0), Maths::vec2f(width, height), 0xffffffff)
		{
			this->position = m_Position;
			m_Texture = texture;
		}
	}
}