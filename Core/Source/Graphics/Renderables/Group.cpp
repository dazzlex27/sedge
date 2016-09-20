#include "Group.h"

namespace S3DGE
{
	namespace Graphics
	{
		Group::Group()
		{
		}

		Group::~Group()
		{
			for (auto item : _renderables)
				SafeDelete(item);
		}

		void Group::Add(Renderable2D* renderable)
		{
			_renderables.push_back(renderable);
		}

		void Group::Submit(Renderer2D* renderer)
		{
			for (auto item : _renderables)
				renderer->SubmitRenderable(item);
		}
	}
}