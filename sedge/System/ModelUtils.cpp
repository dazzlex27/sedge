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

#define TINYOBJLOADER_IMPLEMENTATION
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include <tiny_obj_loader.h>


using namespace std;
using namespace sedge;

// static void ProcessNode(vector<Mesh*>& meshes, const aiNode& node, const aiScene& scene, const string& rootDir);
// static Mesh*const ExtractMesh(const aiMesh& sceneMesh, const aiScene& scene, const string& rootDir);
// static const vector<VertexData> ExtractVertices(const aiMesh& mesh);
// static const vector<uint> ExtractElements(const aiMesh& mesh);
// static const pair<vector<Texture2D*>, vector<Texture2D*>> ExtractTextures(const aiMesh& mesh, const aiScene& scene, const string& rootDir);
// static const vector<Texture2D*> LoadMaterialTextures(const aiMaterial& material, const aiTextureType textureType, const string& rootDir);

Model*const ModelUtils::ReadFromFile(const char*const filepath)
{
	if (!FileUtils::CheckFileExists(filepath))
	{
		LOG_FATAL("Failed to find model file at \"", filepath, "\"");
		return nullptr;
	}

	// Get the directory of the file for loading textures and materials
	const string& fullpath = string(filepath);
	const string& rootDir = fullpath.substr(0, fullpath.find_last_of("/") + 1);

    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = rootDir; // Path to material files

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath);
	
	if (!ret)
	{
		LOG_FATAL("Failed to load OBJ file: ", err);
		return nullptr;
	}

	LOG_INFO("Loading model \"", filepath, "\"...");

	vector<Mesh*> meshes;
	meshes.reserve(shapes.size());

	// Process each shape
	for (const auto& shape : shapes)
	{
		LOG_INFO("Extracting mesh \"", shape.name, "\"...");

		vector<VertexData> vertices;
		vector<uint> elements;

		// Process vertices and indices
		for (size_t i = 0; i < shape.mesh.indices.size(); i++)
		{
			const tinyobj::index_t& idx = shape.mesh.indices[i];
			VertexData vertex;

			// Position (required)
			if (idx.vertex_index >= 0)
			{
				vertex.Position = Vector3(
					attrib.vertices[3 * idx.vertex_index + 0],
					attrib.vertices[3 * idx.vertex_index + 1],
					attrib.vertices[3 * idx.vertex_index + 2]
				);
			}

			// Color (default white)
			vertex.Color = 0xffffffff;

			// Normal
			if (idx.normal_index >= 0)
			{
				vertex.Normal = Vector3(
					attrib.normals[3 * idx.normal_index + 0],
					attrib.normals[3 * idx.normal_index + 1],
					attrib.normals[3 * idx.normal_index + 2]
				);
			}
			else
			{
				vertex.Normal = Vector3(0.0f, 1.0f, 0.0f);
			}

			// TexCoord (UV)
			if (idx.texcoord_index >= 0 && !attrib.texcoords.empty())
			{
				vertex.UV = Vector2(
					attrib.texcoords[2 * idx.texcoord_index + 0],
					attrib.texcoords[2 * idx.texcoord_index + 1]
				);
			}
			else
			{
				vertex.UV = Vector2(0.0f, 0.0f);
			}

			vertices.emplace_back(vertex);
			elements.emplace_back(i);
		}

		// Load textures from material
		vector<Texture2D*> diffTextures;
		vector<Texture2D*> specTextures;

		if (shape.mesh.material_ids.size() > 0)
		{
			int materialID = shape.mesh.material_ids[0];
			if (materialID >= 0 && materialID < materials.size())
			{
				const tinyobj::material_t& material = materials[materialID];

				// Load diffuse textures
				if (!material.diffuse_texname.empty())
				{
					const string& texturePath = rootDir + material.diffuse_texname;
					Texture2D* texture = TextureFactory::CreateTexture2DFromFile(
						material.diffuse_texname.c_str(), 
						texturePath.c_str(), 
						Diffuse
					);
					if (texture)
						diffTextures.emplace_back(texture);
				}

				// Load specular textures
				if (!material.specular_texname.empty())
				{
					const string& texturePath = rootDir + material.specular_texname;
					Texture2D* texture = TextureFactory::CreateTexture2DFromFile(
						material.specular_texname.c_str(), 
						texturePath.c_str(), 
						Specular
					);
					if (texture)
						specTextures.emplace_back(texture);
				}
			}
		}

		// Create mesh
		Mesh* mesh = MeshFactory::CreateMesh(
			shape.name.c_str(),
			vertices,
			elements,
			diffTextures,
			specTextures
		);

		meshes.emplace_back(mesh);
	}

	if (meshes.empty())
	{
		LOG_WARNING("No meshes found in model \"", filepath, "\"");
		return nullptr;
	}

	LOG_INFO("Successfully loaded model with ", (uint)meshes.size(), " mesh(es)");
	return new Model(meshes);
}

// static void ProcessNode(vector<Mesh*>& meshes, const aiNode& node, const aiScene& scene, const string& rootDir)
// {
// 	for (uint i = 0; i < node.mNumMeshes; i++)
// 	{
// 		const aiMesh*const sceneMesh = scene.mMeshes[node.mMeshes[i]];
		
// 		const char*const meshName = sceneMesh->mName.C_Str();
// 		Mesh*const resultMesh = ExtractMesh(*sceneMesh, scene, rootDir);

// 		meshes.emplace_back(resultMesh);
// 	}

// 	for (uint i = 0; i < node.mNumChildren; i++)
// 		ProcessNode(meshes, *(node.mChildren[i]), scene, rootDir);
// }

// static Mesh*const ExtractMesh(const aiMesh& sceneMesh, const aiScene& scene, const string& rootDir)
// {
// 	LOG_INFO("Extracting mesh \"", sceneMesh.mName.C_Str(), "\"...");

// 	vector<VertexData> vertices = ExtractVertices(sceneMesh);

// 	vector<uint> elements = ExtractElements(sceneMesh);

// 	pair<vector<Texture2D*>, vector<Texture2D*>> textures = ExtractTextures(sceneMesh, scene, rootDir);

// 	return MeshFactory::CreateMesh(sceneMesh.mName.C_Str(), vertices, elements, textures.first, textures.second);
// }

// const vector<VertexData> ExtractVertices(const aiMesh& mesh)
// {
// 	vector<VertexData> vertices;
// 	vertices.reserve(mesh.mNumVertices);

// 	for (uint i = 0; i < mesh.mNumVertices; i++)
// 	{
// 		VertexData vertex;

// 		vertex.Position = Vector3(mesh.mVertices[i].x, mesh.mVertices[i].y, mesh.mVertices[i].z);
// 		vertex.Color = 0xffffffff;

// 		if (mesh.HasNormals())
// 			vertex.Normal = Vector3(mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z);

// 		if (mesh.HasVertexColors(0))
// 		{
// 			// TODO
// 		}

// 		if (mesh.HasTextureCoords(0))
// 			vertex.UV = Vector2(mesh.mTextureCoords[0][i].x, mesh.mTextureCoords[0][i].y);
// 		else
// 			vertex.UV = Vector2();

// 		vertices.emplace_back(vertex);
// 	}

// 	return vertices;
// }

// const vector<uint> ExtractElements(const aiMesh& mesh)
// {
// 	vector<uint> elements;
// 	int elementCount = 0;
// 	for (uint i = 0; i < mesh.mNumFaces; i++)
// 		elementCount += mesh.mFaces[i].mNumIndices;
// 	elements.reserve(elementCount);

// 	for (uint i = 0; i < mesh.mNumFaces; i++)
// 	{
// 		const aiFace& face = mesh.mFaces[i];
// 		for (uint j = 0; j < face.mNumIndices; j++)
// 			elements.emplace_back(face.mIndices[j]);
// 	}

// 	return elements;
// }

// static const pair<vector<Texture2D*>, vector<Texture2D*>> ExtractTextures(const aiMesh& mesh, const aiScene& scene, const string& rootDir)
// {
// 	vector<Texture2D*> diffTextures;
// 	vector<Texture2D*> specTextures;

// 	if (mesh.mMaterialIndex >= 0)
// 	{
// 		const aiMaterial& material = *(scene.mMaterials[mesh.mMaterialIndex]);
// 		diffTextures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, rootDir);
// 		specTextures = LoadMaterialTextures(material, aiTextureType_SPECULAR, rootDir);
// 	}

// 	return pair<vector<Texture2D*>, vector<Texture2D*>>(diffTextures, specTextures);
// }

// static const vector<Texture2D*> LoadMaterialTextures(const aiMaterial& material, const aiTextureType textureType, const string& rootDir)
// {
// 	const uint textureCount = material.GetTextureCount(textureType);

// 	vector<Texture2D*> textures;
// 	textures.reserve(textureCount);

// 	for (uint i = 0; i < textureCount; i++)
// 	{
// 		TextureType outType;
// 		switch (textureType)
// 		{
// 		case aiTextureType_DIFFUSE:
// 			outType = Diffuse;
// 			break;
// 		case aiTextureType_SPECULAR:
// 			outType = Specular;
// 			break;
// 		default:
// 			outType = Diffuse;
// 		}

// 		aiString textureName;
// 		material.GetTexture(textureType, i, &textureName);
// 		const string& fullpath = rootDir + string(textureName.C_Str());

// 		Texture2D* texture = TextureFactory::CreateTexture2DFromFile(textureName.C_Str(), fullpath.c_str(), outType);

// 		textures.emplace_back(texture);
// 	}

// 	return textures;
// }