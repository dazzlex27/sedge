#include "Model.h"
#include "Mesh.h"
#include "Graphics/Renderers/Renderer.h"

using namespace s3dge;
using namespace std;

//void Model::Submit(Renderer*const renderer) const
//{
//	for (uint i = 0; i < _meshes.size(); i++)
//		renderer->Submit(_meshes[i]);
//}

Model::Model(const vector<Mesh*> meshes)
{
	_meshes = meshes;
}

void Model::Draw() const
{
	if (_meshes.empty())
		return;

	for (uint i = 0; i < _meshes.size(); i++)
		_meshes[i]->Draw();
}
