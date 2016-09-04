#pragma once

#include "Maths/MathsHeader.h"
#include "Graphics/Texture.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Renderable2D
		{
		protected:
			Maths::vec3f m_Position;
			Maths::vec2f m_Size;
			uint m_Color;
			Texture* m_Texture;


		protected:
			Renderable2D(const Maths::vec3f& position, const Maths::vec2f& size, uint color)
				: m_Position(position), m_Size(size), m_Color(color) 
			{}

		public:
			virtual ~Renderable2D() { SafeDelete(m_Texture); }

			inline const Maths::vec3f GetPosition() const { return m_Position; }
			inline const Maths::vec2f GetSize() const { return m_Size; }
			inline uint GetColor() const { return m_Color; }
			inline const uint GetTextureID() const { return m_Texture == nullptr ? 0 : m_Texture->GetTextureID(); }
		};
	}
}