/*
===========================================================================
Texture.h

Defines a class responsible for processing 2D textures.
===========================================================================
*/

#pragma once

#include <GL/glew.h>
#include "CustomTypes.h"

namespace s3dge
{
	namespace graphics
	{
		class Texture2D
		{
		private:
			cstring _name;
			cstring _path;
			uint _id;
			int _width;
			int _height;
			int _components;

		public:
			Texture2D(cstring name, cstring path);
			~Texture2D();

		public:
			inline cstring GetName() const { return _name; }
			inline uint GetID() const { return _id; }
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