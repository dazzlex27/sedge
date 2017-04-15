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
	namespace graphics
	{
		class GraphicsManager
		{
		private:
			static std::map<cstring, Sprite*> _sprites;
			static std::map<cstring, Label*> _labels;
			static std::map<cstring, Group*> _groups;
			static std::map<cstring, Mesh*> _meshes;
			static bool _initialized;

		public:
			static void Initialize(); // must be called upon engine startup
			static void AddSprite(cstring name, Sprite* sprite, bool overwrite = false);
			static void AddLabel(cstring name, Label* label, bool overwrite = false);
			static void AddGroup(cstring name, bool overwrite = false);
			static void AddMesh(cstring name, Mesh* mesh, bool overwrite = false);
			static Sprite* GetSprite(cstring name);
			static Label* GetLabel(cstring name);
			static Group* GetGroup(cstring name);
			static Mesh* GetMesh(cstring name);
			static void Dispose(); // must be called upon engine shutdown

			static inline uint GetSpriteCount() { return _sprites.size(); }
			static inline uint GetLabelCount() { return _labels.size(); }
			static inline uint GetGroupCount() { return _groups.size(); }
			static inline uint GetMeshCount() { return _meshes.size(); }
		};
	}
}