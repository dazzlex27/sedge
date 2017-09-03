#include "ModelUtils.h"
#include "FileUtils.h"
#include "Log.h"
#include <string>

#include "Graphics/Renderables/Model.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Renderables/MeshFactory.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Managers/TextureManager.h"
#include "Graphics/Textures/TextureFactory.h"
#include "Graphics/Managers/Renderable3DManager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace s3dge;

static void ProcessNode(vector<Mesh*>& meshes, const aiNode*const node, const aiScene*const scene, const string& rootDir);
static Mesh* ProcessMesh(const aiMesh*const mesh, const aiScene*const scene, const string& rootDir);
static void LoadMaterialTextures(vector<id>& textures, aiMaterial* material, aiTextureType textureType, const string& rootDir);

Model* ModelUtils::ReadFromFile(const char* filepath)
{
	if (!FileUtils::CheckFileExists(filepath))
	{
		LOG_ERROR("Failed to open model at \"", filepath, "\"");
		return nullptr;
	}
	
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	string rootDir = string(filepath);
	rootDir = rootDir.substr(0, rootDir.find_last_of("/") + 1);

	vector<Mesh*> meshes;

	ProcessNode(meshes, scene->mRootNode, scene, rootDir);

	return new Model(meshes);
}

static void ProcessNode(vector<Mesh*>& meshes, const aiNode*const node, const aiScene*const scene, const string& rootDir)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		
		const char* meshName = mesh->mName.C_Str();
		Renderable3DManager::AddMesh(meshName, ProcessMesh(mesh, scene, rootDir));
		meshes.push_back(Renderable3DManager::GetMesh(meshName));
	}

	for (uint i = 0; i < node->mNumChildren; i++)
		ProcessNode(meshes, node->mChildren[i], scene, rootDir);
}

static Mesh* ProcessMesh(const aiMesh*const mesh, const aiScene*const scene, const string& rootDir)
{
	vector<VertexData> vertices;
	vector<uint> elements;
	vector<id> textures;

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		VertexData vertex;
		
		vertex.Position = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Color = 0xffffffff;

		if (mesh->HasNormals())
			vertex.Normal = Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if (mesh->HasVertexColors(0))
		{
			// TODO
		}

		if (mesh->HasTextureCoords(0))
			vertex.UV = Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex.UV = Vector2();

		vertices.push_back(vertex);
	}

	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint j = 0; j < face.mNumIndices; j++)
			elements.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		LoadMaterialTextures(textures, material, aiTextureType_DIFFUSE, rootDir);
		//LoadMaterialTextures(textures, material, aiTextureType_SPECULAR, rootDir);
	}

	return MeshFactory::CreateMesh(vertices.data(), vertices.size(), elements.data(), elements.size(), textures.data(), textures.size());
}

static void LoadMaterialTextures(vector<id>& textures, aiMaterial* material, aiTextureType textureType, const string& rootDir)
{
	for (uint i = 0; i < material->GetTextureCount(textureType); i++)
	{
		aiString textureName;
		material->GetTexture(textureType, i, &textureName);
		string fullpath = rootDir + string(textureName.C_Str());

		TextureType outType;
		switch (textureType)
		{
		case aiTextureType_DIFFUSE:
			outType = Diffuse;
			break;
		case aiTextureType_SPECULAR:
			outType = Specular;
			break;
		default:
			outType = Diffuse;
		}

		TextureManager::AddTex2D(textureName.C_Str(), fullpath.c_str(), outType);
		textures.push_back(TextureManager::GetTex2D(textureName.C_Str())->GetID());
	}
}