#pragma once

#include <vector>
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Renderer2D.h"
#include "Graphics/Shaders/ShaderProgram.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Layer
		{
		private:
			std::vector<Renderable2D*> _renderables;
			ShaderProgram* _shaderProgram;
			Renderer2D* _renderer;

		public:
			Layer(ShaderProgram* shaderProgram, Renderer2D* renderer);
			~Layer();

			void Add(Renderable2D* renderable);
			void Render();
		};
	}
}