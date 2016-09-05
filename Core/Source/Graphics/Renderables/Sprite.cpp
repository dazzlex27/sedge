#include "Sprite.h"

namespace S3DGE
{
	namespace Graphics
	{
		Sprite::Sprite(int x, int y, int width, int height, Maths::vec4f color)
			: Renderable2D(Maths::vec3f((float)x, (float)y, 0), Maths::vec2f((float)width, (float)height), color)
		{
		}

		Sprite::Sprite(int x, int y, int width, int height, Texture* texture)
			: Renderable2D(Maths::vec3f((float)x, (float)y, 0), Maths::vec2f((float)width, (float)height), Maths::vec4f(1, 0, 1, 1))
		{
			m_Texture = texture;
		}
	}
}