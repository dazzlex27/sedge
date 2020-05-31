#include "MeshFactory.h"
#include "Mesh.h"
#include "System/Logger.h"
#include "Graphics/Structures/VertexData.h"
#include "System/MemoryManagement.h"
#include "Graphics/Textures/Texture2D.h"

using namespace std;
using namespace sedge;

Mesh*const MeshFactory::CreateMesh(const char*const name,
	vector<VertexData> vertices,
	vector<uint> elements,
	vector<Texture2D*> diffTextures,
	vector<Texture2D*> specTextures)
{
	return new Mesh(name, vertices, elements, diffTextures, specTextures);
}