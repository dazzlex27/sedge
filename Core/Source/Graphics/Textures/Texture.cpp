/*
===========================================================================
Texture.cpp

implements the 2D texture class
===========================================================================
*/

#include "Texture.h"
#include "Utilities/ImageUtils.h"
#include "Internal/DeleteMacros.h"
#include "Internal/Log.h"

namespace s3dge
{
	namespace Graphics
	{
		Texture::Texture(cstring name, cstring path)
			: _name(name), _path(path)
		{
			_id = Load();

			if (_id == -1)
				LOG_ERROR("Failed to load texture: ", name);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &_id);
		}

		uint Texture::Load()
		{
			uint id;

			byte* imagePixels = LoadImage(_path, &_width, &_height, &_components);

			if (imagePixels == nullptr)

				return -1;

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagePixels);

			glBindTexture(GL_TEXTURE_2D, 0);

			SafeDeleteArray(imagePixels);

			return id;
		}

		void Texture::Bind() const
		{
			glBindTexture(GL_TEXTURE_2D, _id);
		}

		void Texture::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}