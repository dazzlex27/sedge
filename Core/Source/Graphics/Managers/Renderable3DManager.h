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
		static std::map<std::string, Mesh*> _meshes;
		static std::map<std::string, Model*> _models;
		static std::map<std::string, Skybox*> _skyboxes;
		static bool _initialized;

	public:
		static void Initialize(); // must be called upon engine startup
		static void AddMesh(const char*const name, Mesh*const mesh, const bool overwrite = false);
		static void AddModel(const char*const name, Model*const model, const bool overwrite = false);
		static void AddSkybox(const char*const name, Skybox*const skybox, const bool overwrite = false);
		static Mesh*const GetMesh(const char*const name);
		static Model*const GetModel(const char*const name);
		static Skybox*const GetSkybox(const char*const name);
		static void Dispose(); // must be called upon engine shutdown

		static inline const uint GetMeshCount() { return _meshes.size(); }
		static inline const uint GetModelCount() { return _models.size(); }
		static inline const uint GetSkyboxCount() { return _skyboxes.size(); }
	};
}