#pragma once

#include <GL/glew.h>
#include "Utilities/ImageLoad.h"
#include "S3DGETypes.h"
#include "Utilities/DeleteMacros.h"
#include "Utilities/Log.h"

namespace s3dge
{
	namespace Graphics
	{
		class Texture
		{
		private:
			cstring m_Name;
			cstring m_Filename;
			uint m_TextureID;
			int m_Width;
			int m_Height;
			int m_Components;

		public:
			Texture(cstring name, cstring filename);
			~Texture();

		public:
			inline cstring GetName() const { return m_Name; }
			inline uint GetTextureID() const { return m_TextureID; }
			inline int GetWidth() const { return m_Width; }
			inline int GetHeight() const { return m_Height; }
			inline int GetComponentsCount() const { return m_Components; }

			void Bind() const;
			void Unbind() const;

		private:
			uint Load();
		};
	}
}