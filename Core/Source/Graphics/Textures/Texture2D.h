/*
===========================================================================
Texture.h

Defines a class responsible for processing 2D textures.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	enum TextureWrapMode
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum TextureFilterMode
	{
		NEAREST = 0,
		LINEAR = 1,
		MIPMAP_NEAREST_NEAREST = 2,
		MIPMAP_LINEAR_NEAREST = 3,
		MIPMAP_NEAREST_LINEAR = 4,
		MIPMAP_LINEAR_LINEAR = 5
	};

	class Texture2D
	{
	private:
		cstring _name;
		cstring _path;
		id _id;
		int _width;
		int _height;
		int _components;
		TextureWrapMode _wrapMode;
		TextureFilterMode _filterMode;

	public:
		Texture2D(cstring name, cstring path, TextureWrapMode wrapMode = REPEAT, TextureFilterMode filterMode = LINEAR);
		~Texture2D();

	public:
		inline cstring GetName() const { return _name; }
		inline id GetID() const { return _id; }
		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }
		inline int GetComponentsCount() const { return _components; }
		inline TextureWrapMode GetWrapMode() const { return _wrapMode; }
		inline TextureFilterMode GetFilterMode() const { return _filterMode; }

		void SetWrapMode(TextureWrapMode wrapMode);
		void SetFilterMode(TextureFilterMode filterMode);

		void Bind() const;
		void Unbind() const;

		void AssignToPosition(const float position);

	private:
		bool Load();

		friend class TextureFactory;
	};
}