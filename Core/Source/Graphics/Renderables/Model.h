#pragma once

#include <vector>
#include "Renderable3D.h"

namespace s3dge
{
	class Mesh;

	class Model : public Renderable3D
	{
	private:
		std::vector<Mesh*> _meshes;

	public:
		bool LoadModel(const char* path);
		virtual void Draw() const override;
	};
}