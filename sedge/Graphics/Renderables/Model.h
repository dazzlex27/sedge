/*
===========================================================================
Mode.h

Declares the Model class
A model is a collection of meshes.
TODO: implement transformation for a model (that is for all meshes in a model).
===========================================================================
*/

#pragma once

#include <vector>
#include "Renderable3D.h"

namespace sedge
{
	class Mesh;

	class Model : public Renderable3D
	{
	private:
		std::vector<Mesh*> _meshes;

	public:
		Model(const std::vector<Mesh*> meshes);

		virtual void Draw() const override;
	};
}