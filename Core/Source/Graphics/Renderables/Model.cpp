#include "Model.h"
#include "Mesh.h"
#include "Graphics/Renderers/Renderer.h"

using namespace s3dge;

bool Model::LoadModel(cstring path)
{
	// TODO:

	return false;
}

void Model::Submit(Renderer*const renderer) const
{
	for (uint i = 0; i < _meshes.size(); i++)
		renderer->Submit(_meshes[i]);
}

void Model::Draw() const
{
	for (uint i = 0; i < _meshes.size(); i++)
		_meshes[i]->Draw();
}
