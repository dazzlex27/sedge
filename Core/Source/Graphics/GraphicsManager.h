/*
===========================================================================
GraphicsManager.h

Defines a class responsible for managing Renderable objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>
#include "Renderables/Group.h"
#include "Renderables/Label.h"
#include "Renderables/Sprite.h"
#include "Renderables/Mesh.h"

namespace s3dge
{
	class GraphicsManager
	{
	private:
		static std::map<const char*, Sprite*> _sprites;
		static std::map<const char*, Label*> _labels;
		static std::map<const char*, Group*> _groups;
		static std::map<const char*, Mesh*> _meshes;
		static bool _initialized;

	public:
		static void Initialize(); // must be called upon engine startup
		static void AddSprite(const char* name, Sprite* sprite, bool overwrite = false);
		static void AddLabel(const char* name, Label* label, bool overwrite = false);
		static void AddGroup(const char* name, bool overwrite = false);
		static void AddMesh(const char* name, Mesh* mesh, bool overwrite = false);
		static Sprite* GetSprite(const char* name);
		static Label* GetLabel(const char* name);
		static Group* GetGroup(const char* name);
		static Mesh* GetMesh(const char* name);
		static void Dispose(); // must be called upon engine shutdown

		static inline uint GetSpriteCount() { return _sprites.size(); }
		static inline uint GetLabelCount() { return _labels.size(); }
		static inline uint GetGroupCount() { return _groups.size(); }
		static inline uint GetMeshCount() { return _meshes.size(); }
	};
}