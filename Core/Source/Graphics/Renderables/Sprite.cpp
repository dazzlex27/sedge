#include "Sprite.h"

namespace S3DGE
{
	namespace Graphics
	{
		Sprite::Sprite(float x, float y, float width, float height, uint color)
			: Renderable2D(Maths::vec3f(x, y, 0), Maths::vec2f(width, height), color)
		{
		}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(Maths::vec3f(x, y, 0), Maths::vec2f(width, height), 255)
		{
			m_Texture = texture;
		}
	}
}