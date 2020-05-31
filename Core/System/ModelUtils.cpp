#include "ModelUtils.h"
#include "FileUtils.h"
#include "Logger.h"
#include <string>

#include "Graphics/Renderables/Model.h"
#include "Graphics/Renderables/MeshFactory.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/TextureFactory.h"
#include "Graphics/AssetManagers/TextureManager.h"
#include "Graphics/AssetManagers/Renderable3DManager.h"
#include "Graphics/Structures/VertexData.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace s3dge;

static void ProcessNode(vector<Mesh*>& meshes, const aiNode& node, const aiScene& scene, const string& rootDir);
static Mesh*const ExtractMesh(const aiMesh& sceneMesh, const aiScene& scene, const string& rootDir);
static const vector<VertexData> ExtractVertices(const aiMesh& mesh);
static const vector<uint> ExtractElements(const aiMesh& mesh);
static const pair<vector<Texture2D*>, vector<Texture2D*>> ExtractTextures(const aiMesh& mesh, const aiScene& scene, const string& rootDir);
static const vector<Texture2D*> LoadMaterialTextures(const aiMaterial& material, const aiTextureType textureType, const string& rootDir);

Model*const ModelUtils::ReadFromFile(const char*const filepath)
{
	if (!FileUtils::CheckFileExists(filepath))
	{
		LOG_FATAL("Failed to find model file at \"", filepath, "\"");
		return nullptr;
	}
	
	Assimp::Importer importer;
	const aiScene*const scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	const string& fullpath = string(filepath);
	const string& rootDir = fullpath.substr(0, fullpath.find_last_of("/") + 1);

	vector<Mesh*> meshes;
	meshes.reserve(scene->mNumMeshes);


	LOG_INFO("Loading model \"", filepath, "\"...");
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

		meshes.emplace_back(resultMesh);
	}

	for (uint i = 0; i < node.mNumChildren; i++)
		ProcessNode(meshes, *(node.mChildren[i]), scene, rootDir);
}

static Mesh*const ExtractMesh(const aiMesh& sceneMesh, const aiScene& scene, const string& rootDir)
{
	LOG_INFO("Extracting mesh \"", sceneMesh.mName.C_Str(), "\"...");

	vector<VertexData> vertices = ExtractVertices(sceneMesh);

	vector<uint> elements = ExtractElements(sceneMesh);

	pair<vector<Texture2D*>, vector<Texture2D*>> textures = ExtractTextures(sceneMesh, scene, rootDir);

	return MeshFactory::CreateMesh(sceneMesh.mName.C_Str(), vertices, elements, textures.first, textures.second);
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

static const pair<vector<Texture2D*>, vector<Texture2D*>> ExtractTextures(const aiMesh& mesh, const aiScene& scene, const string& rootDir)
{
	vector<Texture2D*> diffTextures;
	vector<Texture2D*> specTextures;

	if (mesh.mMaterialIndex >= 0)
	{
		const aiMaterial& material = *(scene.mMaterials[mesh.mMaterialIndex]);
		diffTextures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, rootDir);
		specTextures = LoadMaterialTextures(material, aiTextureType_SPECULAR, rootDir);
	}

	return pair<vector<Texture2D*>, vector<Texture2D*>>(diffTextures, specTextures);
}

static const vector<Texture2D*> LoadMaterialTextures(const aiMaterial& material, const aiTextureType textureType, const string& rootDir)
{
	const uint textureCount = material.GetTextureCount(textureType);

	vector<Texture2D*> textures;
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

		Texture2D* texture = TextureFactory::CreateTexture2DFromFile(textureName.C_Str(), fullpath.c_str(), outType);

		textures.emplace_back(texture);
	}

	return textures;
}