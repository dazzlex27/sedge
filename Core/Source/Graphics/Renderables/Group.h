#pragma once

#include "Renderable2D.h"
#include "Graphics/Renderer2D.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> _renderables;

		public:
			Group();
			~Group();

			void Add(Renderable2D* renderable);
			void Submit(Renderer2D* renderer);
		};
	}
}