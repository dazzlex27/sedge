/*
===========================================================================
Cubemap.h

Defines a class responsible for processing cubical textures.
===========================================================================
*/

#pragma once

#include "Texture.h"
#include <vector>
#include <string>

namespace s3dge
{
	class Cubemap : public Texture
	{
	private:
		std::vector<std::string> _paths;

	private:
		Cubemap(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);

		friend class TextureFactory;

	private:
		virtual bool Load() override;
	};
}