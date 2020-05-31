/*
===========================================================================
Texture.h

Base class for texture objects.
===========================================================================
*/

#pragma once

#include <string>
#include <CustomTypes.h>
#include "TextureEnums.h"

namespace sedge
{
	class Texture
	{
	protected:
		std::string Name;
		std::string Path;
		ID TextureID;
		TextureTarget Target;
		TextureWrapMode WrapMode;
		TextureFilterMode FilterMode;

	protected:
		Texture() {}
		Texture(const char* name, const char* path, const TextureTarget target, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);
		virtual ~Texture();

	public:
		const char* GetName() const { return Name.c_str(); }
		const char* GetPath() const { return Path.c_str(); }
		const ID GetID() const { return TextureID; }
		const TextureTarget GetTarget() const { return Target; }
		const TextureWrapMode GetWrapMode() const { return WrapMode; }
		const TextureFilterMode GetFilterMode() const { return FilterMode; }

		virtual void Bind() const;
		virtual void Unbind() const;

		static void ActivateTexture(const uint num);
		static void BindById(const TextureTarget target, const ID texId);

		virtual void SetWrapMode(const TextureWrapMode Mode);
		virtual void SetFilterMode(const TextureFilterMode Mode);

	private:
		virtual bool Load() = 0;
	};
}