#include "ModelUtils.h"
#include "FileUtils.h"
#include "Log.h"
#include <string>

#include "Graphics/Renderables/Model.h"
#include "Graphics/Renderables/MeshFactory.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/TextureFactory.h"
#include "Graphics/Managers/TextureManager.h"
#include "Graphics/Managers/Renderable3DManager.h"
#include "Graphics/Structures/VertexData.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace s3dge;

static void ProcessNode(vector<Mesh*>& meshes, const aiNode& node, const aiScene& scene, const string& rootDir);
static Mesh*const ExtractMesh(const aiMesh& mesh, const aiScene& scene, const string& rootDir);
static const vector<VertexData> ExtractVertices(const aiMesh& mesh);
static const vector<uint> ExtractElements(const aiMesh& mesh);
static const pair<vector<ID>, vector<ID>> ExtractTextures(const aiMesh& mesh, const aiScene& scene, const string& rootDir);
static const vector<ID> LoadMaterialTextures(const aiMaterial& material, const aiTextureType textureType, const string& rootDir);

Model*const ModelUtils::ReadFromFile(const char*const filepath)
{
	if (!FileUtils::CheckFileExists(filepath))
	{
		LOG_ERROR("Failed to open model at \"", filepath, "\"");
		return nullptr;
	}
	
	Assimp::Importer importer;
	const aiScene*const scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	const string& fullpath = string(filepath);
	const string& rootDir = fullpath.substr(0, fullpath.find_last_of("/") + 1);

	vector<Mesh*> meshes;
	meshes.reserve(scene->mNumMeshes);

	ProcessNode(meshes, *(scene->mRootNode), *scene, rootDir);

	return new Model(meshes);
}

static void ProcessNode(vector<Mesh*>& meshes, const aiNode& node, const aiScene& scene, const string& rootDir)
{
	for (uint i = 0; i < node.mNumMeshes; i++)
	{
		const aiMesh*const sceneMesh = scene.mMeshes[node.mMeshes[i]];
		
		const char*const meshName = sceneMesh->mName.C_Str();
		Mesh*const resultMesh = ExtractMesh(*sceneMesh, scene, rootDir);

		Renderable3DManager::AddMesh(meshName, resultMesh);
		meshes.emplace_back(Renderable3DManager::GetMesh(meshName));
	}

	for (uint i = 0; i < node.mNumChildren; i++)
		ProcessNode(meshes, *(node.mChildren[i]), scene, rootDir);
}

static Mesh*const ExtractMesh(const aiMesh& mesh, const aiScene& scene, const string& rootDir)
{
	vector<VertexData> vertices = ExtractVertices(mesh);

	vector<uint> elements = ExtractElements(mesh); 

	pair<vector<ID>, vector<ID>> textures = ExtractTextures(mesh, scene, rootDir);

	return MeshFactory::CreateMesh(
		vertices.data(), vertices.size(), 
		elements.data(), elements.size(), 
		textures.first.data(), textures.first.size(),
		textures.second.data(), textures.second.size());
}

const vector<VertexData> ExtractVertices(const aiMesh& mesh)
{
	vector<VertexData> vertices;
	vertices.reserve(mesh.mNumVertices);

	for (uint i = 0; i < mesh.mNumVertices; i++)
	{
		VertexData vertex;

		vertex.Position = Vector3(mesh.mVertices[i].x, mesh.mVertices[i].y, mesh.mVertices[i].z);
		vertex.Color = 0xffffffff;

		if (mesh.HasNormals())
			vertex.Normal = Vector3(mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z);

		if (mesh.HasVertexColors(0))
		{
			// TODO
		}

		if (mesh.HasTextureCoords(0))
			vertex.UV = Vector2(mesh.mTextureCoords[0][i].x, mesh.mTextureCoords[0][i].y);
		else
			vertex.UV = Vector2();

		vertices.emplace_back(vertex);
	}

	return vertices;
}

const vector<uint> ExtractElements(const aiMesh& mesh)
{
	vector<uint> elements;
	int elementCount = 0;
	for (uint i = 0; i < mesh.mNumFaces; i++)
		elementCount += mesh.mFaces[i].mNumIndices;
	elements.reserve(elementCount);

	for (uint i = 0; i < mesh.mNumFaces; i++)
	{
		const aiFace& face = mesh.mFaces[i];
		for (uint j = 0; j < face.mNumIndices; j++)
			elements.emplace_back(face.mIndices[j]);
	}

	return elements;
}

static const pair<vector<ID>, vector<ID>> ExtractTextures(const aiMesh& mesh, const aiScene& scene, const string& rootDir)
{
	vector<ID> diffTextures;
	vector<ID> specTextures;

	if (mesh.mMaterialIndex >= 0)
	{
		const aiMaterial& material = *(scene.mMaterials[mesh.mMaterialIndex]);
		diffTextures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, rootDir);
		specTextures = LoadMaterialTextures(material, aiTextureType_SPECULAR, rootDir);
	}

	return pair<vector<ID>, vector<ID>>(diffTextures, specTextures);
}

static const vector<ID> LoadMaterialTextures(const aiMaterial& material, const aiTextureType textureType, const string& rootDir)
{
	const uint textureCount = material.GetTextureCount(textureType);

	vector<ID> textures;
	textures.reserve(textureCount);

	for (uint i = 0; i < textureCount; i++)
	{
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

		aiString textureName;
		material.GetTexture(textureType, i, &textureName);
		const string& fullpath = rootDir + string(textureName.C_Str());

		TextureManager::AddTex2D(textureName.C_Str(), fullpath.c_str(), outType);
		textures.emplace_back(TextureManager::GetTex2D(textureName.C_Str())->GetID());
	}

	return textures;
}