#pragma once

#include <GL/glew.h>
#include "CustomTypes.h"
#include "Utilities/ImageLoad.h"
#include "Internal/DeleteMacros.h"
#include "Internal/Log.h"

namespace s3dge
{
	namespace Graphics
	{
		class Texture
		{
		private:
			cstring _name;
			cstring _path;
			uint _textureID;
			int _width;
			int _height;
			int _components;

		public:
			Texture(cstring name, cstring path);
			~Texture();

		public:
			inline cstring GetName() const { return _name; }
			inline uint GetTextureID() const { return _textureID; }
			inline int GetWidth() const { return _width; }
			inline int GetHeight() const { return _height; }
			inline int GetComponentsCount() const { return _components; }

			void Bind() const;
			void Unbind() const;

		private:
			uint Load();
		};
	}
}