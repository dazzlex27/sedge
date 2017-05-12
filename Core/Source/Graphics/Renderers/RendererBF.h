#pragma once

#include <vector>
#include "Renderer.h"

namespace s3dge
{
	namespace graphics
	{
		class Mesh;

		class RendererBF : public Renderer
		{
		private:
			std::vector<const Mesh*> _renderables;

		public:
			RendererBF();
			virtual ~RendererBF();

			virtual void Begin() override;
			virtual void SubmitMesh(const Mesh* mesh) override;
			virtual void Flush() override;
			virtual void End() override;
		};
	}
}