#include "Renderer2D.h"

namespace s3dge
{
	namespace Graphics
	{
		Renderer2D::Renderer2D()
		{			
			Initialize();
		}

		Renderer2D::~Renderer2D()
		{
			SafeDelete(m_IBO);
			glDeleteBuffers(1, &m_VBO);
			glDeleteVertexArrays(1, &m_VAO);
		}

		void Renderer2D::Initialize()
		{
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::vertex)));
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::color)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::textureID)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			uint* indices = new uint[RENDERER_INDICES_SIZE];

			int offset = 0;

			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);

			m_Atlas = ftgl::texture_atlas_new(512, 512, 2);
			m_Font = ftgl::texture_font_new_from_file(m_Atlas, 32, "Resources\\SourceSansPro-Light.ttf");
		}

		void Renderer2D::Begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void Renderer2D::SubmitRenderable(const Renderable2D* renderable)
		{
			const Maths::vec3f& position = renderable->GetPosition();
			const Maths::vec2f& size = renderable->GetSize();
			const uint color = renderable->GetColor();
			const std::vector<Maths::vec2f> uv = renderable->GetUV();
			const uint textureID = renderable->GetTextureID();

			float textureSlot = 0.0f;

			if (textureID > 0)
			{
				bool ok = false;
				for (uint i = 0; i < m_Textures.size(); ++i)
				{
					if (m_Textures[i] == textureID)
					{
						textureSlot = (float)(i + 1);
						ok = true;
						break;
					}
				}

				if (!ok)
				{
					if (m_Textures.size() >= 32)
					{
						End();
						Flush();
						Begin();
					}

					m_Textures.push_back(textureID);
					textureSlot = (float)(m_Textures.size());
				}
			}

			m_Buffer->vertex = position;
			m_Buffer->color = color;
			m_Buffer->uv = uv[0];
			m_Buffer->textureID = textureSlot;
			m_Buffer++;

			m_Buffer->vertex = Maths::vec3f(position.x, position.y + size.y, position.z);
			m_Buffer->color = color;
			m_Buffer->uv = uv[1];
			m_Buffer->textureID = textureSlot;
			m_Buffer++;

			m_Buffer->vertex = Maths::vec3f(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->color = color;
			m_Buffer->uv = uv[2];
			m_Buffer->textureID = textureSlot;
			m_Buffer++;

			m_Buffer->vertex = Maths::vec3f(position.x + size.x, position.y, position.z);
			m_Buffer->color = color;
			m_Buffer->uv = uv[3];
			m_Buffer->textureID = textureSlot;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void Renderer2D::SubmitLabel(const Label* label)
		{

			using namespace ftgl;
			std::string text = label->text;
			uint color = label->GetColor();
			Maths::vec3f position = label->GetPosition();
			float x = position.x;

			float textureSlot = 0.0f;

			bool ok = false;
			for (uint i = 0; i < m_Textures.size(); ++i)
			{
				if (m_Textures[i] == m_Atlas->id)
				{
					textureSlot = (float)(i + 1);
					ok = true;
					break;
				}
			}

			if (!ok)
			{
				if (m_Textures.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}

				m_Textures.push_back(m_Atlas->id);
				textureSlot = (float)(m_Textures.size());
			}

			float scaleX = 1280.0f / 32.0f;
			float scaleY = 720.0f / 18.0f;

			for (uint i = 0; i < text.length(); i++)
			{
				texture_glyph_t* glyph = texture_font_get_glyph(m_Font, text[i]);
				if (glyph != NULL)
				{

					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scaleX;
					}

					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_Buffer->vertex = Maths::vec3f(x0, y0, 0);
					m_Buffer->uv = Maths::vec2f(u0, v0);
					m_Buffer->textureID = textureSlot;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = Maths::vec3f(x0, y1, 0);
					m_Buffer->uv = Maths::vec2f(u0, v1);
					m_Buffer->textureID = textureSlot;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = Maths::vec3f(x1, y1, 0);
					m_Buffer->uv = Maths::vec2f(u1, v1);
					m_Buffer->textureID = textureSlot;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = Maths::vec3f(x1, y0, 0);
					m_Buffer->uv = Maths::vec2f(u1, v0);
					m_Buffer->textureID = textureSlot;
					m_Buffer->color = color;
					m_Buffer++;

					m_IndexCount += 6;

					x += glyph->advance_x / scaleX;
				}

			}
		}

		void Renderer2D::Flush()
		{
			for (uint i = 0; i < m_Textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D,m_Textures[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->Bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->Unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}

		void Renderer2D::End()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}