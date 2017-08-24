#include "ModelLoader.h"
#include "FileUtils.h"
#include "System/Log.h"
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace s3dge;

Model* ModelUtils::ReadFromFile(const char* filepath)
{
	if (!FileUtils::CheckFileExists(filepath))
	{
		LOG_ERROR("Failed to open model at \"", filepath, "\"");
		return nullptr;
	}
	
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	return nullptr;
}
