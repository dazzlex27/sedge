#include "Renderer2D.h"

namespace S3DGE
{
	namespace Graphics
	{
		Renderer2D::Renderer2D(ShaderProgram* shaderProgram)
			: m_ShaderProgram(shaderProgram)
		{			
			Initialize();
		}

		Renderer2D::~Renderer2D()
		{
			glDeleteVertexArrays(1, &m_VAO);
		}

		void Renderer2D::Initialize()
		{
			using namespace Maths;

			m_ShaderProgram->Enable();
			mat4 ortho = mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -3.0f, 3.0f);
			mat4 rotate = mat4::Rotate(vec3f(1, 1, 1), 30.0f);
			mat4 translate = mat4::Translate(vec3f(4, 3, 0));
			mat4 scale = mat4::Scale(vec3f(2, 2, 0));
			mat4 modelMatrix = translate;// *rotate * scale;
			m_ShaderProgram->SetUniformMat4fv("pr_matrix", ortho);
			m_ShaderProgram->SetUniformMat4fv("ml_matrix", modelMatrix);
			m_ShaderProgram->SetUniform2f("light_pos", vec2f(2, 1.5));
		}

		void Renderer2D::Submit(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Renderer2D::Flush()
		{
			while (!m_Renderables.empty())
			{
				const Renderable2D* renderable = m_Renderables.front();
				renderable->GetVAO()->Bind();
				renderable->GetIBO()->Bind();
				glDrawElements(GL_TRIANGLES, renderable->GetIBO()->GetCount(), GL_UNSIGNED_SHORT, nullptr);
				renderable->GetVAO()->Unbind();
				renderable->GetIBO()->Unbind();
				m_Renderables.pop_front();
			}
		}
	}
}