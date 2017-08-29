/*
===========================================================================
Cubemap.h

Defines a class responsible for processing cubical textures.
===========================================================================
*/

#pragma once

#include "Texture.h"
#include <vector>

namespace s3dge
{
	class Cubemap : public Texture
	{
	private:
		std::vector<const char*> _paths;

	public:
		Cubemap(const char* name, const std::vector<const char*>& paths, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);

	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;

		friend class TextureFactory;

	private:
		virtual bool Load() override;
	};
}