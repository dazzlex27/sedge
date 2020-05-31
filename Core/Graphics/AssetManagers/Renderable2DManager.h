/*
===========================================================================
Renderable2DManager.h

Defines a class responsible for managing Renderable2D objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>
#include <string>
#include <CustomTypes.h>

namespace s3dge
{
	class Group;
	class Label;
	class Sprite;

	class Renderable2DManager
	{
	private:
		std::map<std::string, Sprite*> _sprites;
		std::map<std::string, Label*> _labels;
		std::map<std::string, Group*> _groups;

	public:
		Renderable2DManager() {}
		~Renderable2DManager();

		void AddSprite(const char* name, Sprite*const sprite, const bool overwrite = false);
		void AddLabel(const char* name, Label*const label, const bool overwrite = false);
		void AddGroup(const char* name, const bool overwrite = false);
		Sprite*const GetSprite(const char* name);
		Label*const GetLabel(const char* name);
		Group*const GetGroup(const char* name);

		inline const uint GetSpriteCount() { return _sprites.size(); }
		inline const uint GetLabelCount() { return _labels.size(); }
		inline const uint GetGroupCount() { return _groups.size(); }

	private:
		Renderable2DManager(const Renderable2DManager& tRef) = delete;
		Renderable2DManager& operator = (const Renderable2DManager& tRef) = delete;

		friend class GraphicsAssetManagerFactory;
	};
}