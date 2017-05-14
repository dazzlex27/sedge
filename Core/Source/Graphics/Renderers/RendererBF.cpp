#include "RendererBF.h"
#include "Graphics/Renderables/Mesh.h"

using namespace s3dge;
using namespace std;

RendererBF::RendererBF()
{
}

RendererBF::~RendererBF()
{
}

void RendererBF::SubmitMesh(const Mesh* mesh)
{
	_renderables.push_back(mesh);
}

void RendererBF::Begin()
{
}

void RendererBF::Flush()
{
	for (uint i = 0; i < _renderables.size(); i++)
		_renderables[i]->Render();
}

void RendererBF::End()
{
}