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

	public:
		Cubemap(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);

	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;

		friend class TextureFactory;

	private:
		virtual bool Load() override;
	};
}