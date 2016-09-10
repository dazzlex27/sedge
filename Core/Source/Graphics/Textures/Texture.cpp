#include "Texture.h"

namespace S3DGE
{
	namespace Graphics
	{
		Texture::Texture(cstring name, cstring filename)
			: m_Name(name), m_Filename(filename)
		{
			m_TextureID = Load();
		}

		Texture::~Texture()
		{
		}

		uint Texture::Load()
		{
			uint textureID;

			byte* imagePixels = LoadImage(m_Filename, &m_Width, &m_Height, &m_Components);

			if (imagePixels == nullptr)
			{
				LOG_ERROR("Failed to load texture");
				return -1;
			}

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagePixels);

			glBindTexture(GL_TEXTURE_2D, 0);

			SafeDeleteArray(imagePixels);

			return textureID;
		}

		void Texture::Bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
		}

		void Texture::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}