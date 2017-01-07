/*
===========================================================================
GraphicsManager.h

Defines a class responsible for managing Renderable objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>
#include <string>
#include "Renderables/Group.h"
#include "Renderables/Label.h"
#include "Renderables/Sprite.h"
#include "Fonts/Font.h"

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
			static bool _initialized;

		public:
			static void Initialize(); // must be called upon engine startup
			static void AddSprite(cstring name, float x, float y, float w, float h, uint c, Texture* t = nullptr, bool overrideExisting = false);
			static void AddLabel(cstring name, const std::string& text, Font* font, float x, float y, float w, float h, uint c = 0xffffffff, bool overrideExisting = false);
			static void AddGroup(cstring name, bool overrideExisting = false);
			static Sprite* GetSprite(cstring name);
			static Label* GetLabel(cstring name);
			static Group* GetGroup(cstring name);
			static void Dispose(); // must be called upon engine shutdown

			static inline uint GetCount() { return _sprites.size() + _labels.size(); }
		};
	}
}