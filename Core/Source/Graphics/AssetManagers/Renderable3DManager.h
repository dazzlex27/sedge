/*
===========================================================================
Renderable3DManager.h

Defines a class responsible for managing Renderable3D objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>
#include "CustomTypes.h"

namespace s3dge
{
	class Mesh;
	class Model;
	class Skybox;

	class Renderable3DManager
	{
	private:
		std::map<std::string, Mesh*> _meshes;
		std::map<std::string, Model*> _models;
		std::map<std::string, Skybox*> _skyboxes;

	public:
		~Renderable3DManager();

		void AddMesh(const char*const name, Mesh*const mesh, const bool overwrite = false);
		void AddModel(const char*const name, Model*const model, const bool overwrite = false);
		void AddSkybox(const char*const name, Skybox*const skybox, const bool overwrite = false);
		Mesh*const GetMesh(const char*const name);
		Model*const GetModel(const char*const name);
		Skybox*const GetSkybox(const char*const name);

		inline const uint GetMeshCount() { return _meshes.size(); }
		inline const uint GetModelCount() { return _models.size(); }
		inline const uint GetSkyboxCount() { return _skyboxes.size(); }

	private:
		Renderable3DManager() {}
		Renderable3DManager(const Renderable3DManager& tRef) = delete;
		Renderable3DManager& operator = (const Renderable3DManager& tRef) = delete;

		friend class GraphicsAssetManagerFactory;
	};
}