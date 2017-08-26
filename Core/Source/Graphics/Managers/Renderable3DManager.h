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

	class Renderable3DManager
	{
	private:
		static std::map<std::string, Mesh*> _meshes;
		static std::map<std::string, Model*> _models;
		static bool _initialized;

	public:
		static void Initialize(); // must be called upon engine startup
		static void AddMesh(const char* name, Mesh* mesh, bool overwrite = false);
		static void AddModel(const char* name, Model* model, bool overwrite = false);
		static Mesh* GetMesh(const char* name);
		static Model* GetModel(const char* name);
		static void Dispose(); // must be called upon engine shutdown

		static inline uint GetMeshCount() { return _meshes.size(); }
		static inline uint GetModelCount() { return _models.size(); }
	};
}