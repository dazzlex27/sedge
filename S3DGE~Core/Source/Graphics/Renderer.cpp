#include "Renderer.h"

namespace S3DGE
{
	namespace Graphics
	{
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
			glCreateVertexArrays(1, &m_VAO);
		}

		void Renderer::Draw()
		{
			srand(time(NULL));
			Maths::vec4f color((float)(rand() / (float)((unsigned)RAND_MAX + 1)), 
				(float)(rand() / (float)((unsigned)RAND_MAX + 1)), 
				(float)(rand() / (float)((unsigned)RAND_MAX + 1)), 
				(float)(rand() / (float)((unsigned)RAND_MAX + 1)));

			float attrib[] = { (float)sin(rand()) * 0.5f,(float)cos(rand()) * 0.6f, 0.0f, 0.0f };
			glVertexAttrib4fv(0, attrib);
			glVertexAttrib4f(1, color.x, color.y, color.z, color.w);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}