/*
===========================================================================
Renderable2DManager.h

Defines a class responsible for managing Renderable2D objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>
#include "CustomTypes.h"

namespace s3dge
{
	class Group;
	class Label;
	class Sprite;

	class Renderable2DManager
	{
	private:
		static std::map<std::string, Sprite*> _sprites;
		static std::map<std::string, Label*> _labels;
		static std::map<std::string, Group*> _groups;
		
		static bool _initialized;

	public:
		static void Initialize(); // must be called upon engine startup
		static void AddSprite(const char* name, Sprite* sprite, bool overwrite = false);
		static void AddLabel(const char* name, Label* label, bool overwrite = false);
		static void AddGroup(const char* name, bool overwrite = false);
		static Sprite* GetSprite(const char* name);
		static Label* GetLabel(const char* name);
		static Group* GetGroup(const char* name);
		static void Dispose(); // must be called upon engine shutdown

		static inline uint GetSpriteCount() { return _sprites.size(); }
		static inline uint GetLabelCount() { return _labels.size(); }
		static inline uint GetGroupCount() { return _groups.size(); }
	};
}