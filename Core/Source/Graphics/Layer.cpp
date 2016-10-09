#include "Layer.h"

namespace s3dge
{
	namespace Graphics
	{
		Layer::Layer(ShaderProgram* shaderProgram, Renderer2D* renderer)
			: _shaderProgram(shaderProgram), _renderer(renderer)
		{
		}

		Layer::~Layer()
		{
			for (auto item : _renderables)
				SafeDelete(item);
		}

		void Layer::Add(Renderable2D* renderable)
		{
			_renderables.push_back(renderable);
		}

		void Layer::Render()
		{
			_shaderProgram->Enable();
			_renderer->Begin();

			for (auto item : _renderables)
				_renderer->SubmitRenderable(item);
			
			_renderer->End();
			_renderer->Flush();
		}
	}
}