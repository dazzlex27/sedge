#pragma once

#include "Maths/MathsHeader.h"
#include "Graphics/Texture.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Utilities/DeleteMacros.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Renderable2D
		{
		protected:
			Maths::vec3f m_Position;
			Maths::vec2f m_Size;
			Maths::vec4f m_Color;
			Texture* m_Texture;
		public:
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;

		public:
			Renderable2D(const Maths::vec3f& position, const Maths::vec2f& size, Maths::vec4f color)
				: m_Position(position), m_Size(size), m_Color(color) 
			{
				float vertices[] =
				{
					0, 0, 0,
					0, m_Size.y, 0,
					m_Size.x, m_Size.y, 0,
					m_Size.x, 0, 0
				};

				float colors[] =
				{
					m_Color.x, m_Color.y,m_Color.z,m_Color.w,
					m_Color.x, m_Color.y,m_Color.z,m_Color.w,
					m_Color.x, m_Color.y,m_Color.z,m_Color.w,
					m_Color.x, m_Color.y,m_Color.z,m_Color.w
				};
				
				m_VertexArray = new VertexArray();

				m_VertexArray->AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_VertexArray->AddBuffer(new Buffer(colors, 4 * 4, 4), 1);

				ushort indices[] = { 0, 1, 2, 2, 3, 0 };
				m_IndexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D() 
			{
				SafeDelete(m_VertexArray);
				SafeDelete(m_IndexBuffer);
				SafeDelete(m_Texture); 
			}
			
			inline const Maths::vec3f GetPosition() const { return m_Position; }
			inline const Maths::vec2f GetSize() const { return m_Size; }
			inline Maths::vec4f GetColor() const { return m_Color; }
			inline const uint GetTextureID() const { return m_Texture == nullptr ? 0 : m_Texture->GetTextureID(); }
			inline VertexArray* GetVAO() const { return m_VertexArray; }
			inline IndexBuffer* GetIBO() const { return m_IndexBuffer; }
		};
	}
}