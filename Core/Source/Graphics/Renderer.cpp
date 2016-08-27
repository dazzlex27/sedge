#include "Renderer.h"

namespace S3DGE
{
	namespace Graphics
	{
		struct Vertex
		{
			float x;
			float y;
			float z;

			float r;
			float g;
			float b;
		};

		Renderer::Renderer(ShaderProgram* shaderProgram)
			: m_ShaderProgram(shaderProgram)
		{			
			Initialize();
		}

		Renderer::~Renderer()
		{
			glDeleteVertexArrays(1, &m_VAO);
		}

		void Renderer::Initialize()
		{
			using namespace Maths;
			float vertices[] =
			{
				1,1,0,
				11,1,0,
				1,6,0
			};

			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			m_ShaderProgram->Enable();
			m_ShaderProgram->SetUniform4f("cl", vec4f(0.2f, 0.3f, 0.8f, 1.0f));
			mat4 ortho = mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
			mat4 rotate = mat4::Rotate(vec3f(0, 0, 1), 1.0f);
			mat4 translate = mat4::Translate(vec3f(1, 0, 0));
			mat4 modelMatrix = translate * rotate;
			m_ShaderProgram->SetUniformMat4fv("pr_matrix", ortho);
			m_ShaderProgram->SetUniform2f("light_pos", vec2f(2, 1.5));
		}

		void Renderer::Draw()
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}