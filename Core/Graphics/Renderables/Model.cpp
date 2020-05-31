/*
===========================================================================
Mesh.cpp

Implements the Model class.
===========================================================================
*/

#include "Model.h"
#include "Mesh.h"

using namespace s3dge;
using namespace std;

Model::Model(const vector<Mesh*> meshes)
	: _meshes(meshes)
{
}

void Model::Draw() const
{
	for (uint i = 0; i < _meshes.size(); i++)
		_meshes[i]->Draw();
}
