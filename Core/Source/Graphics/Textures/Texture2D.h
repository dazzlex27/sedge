/*
===========================================================================
Texture2D.h

Defines a class responsible for processing 2D textures.
===========================================================================
*/

#pragma once

#include "Texture.h"

namespace s3dge
{
	enum TextureType
	{
		Diffuse,
		Specular
	};

	enum TextureWrapMode
	{
	private:
		int _width;
		int _height;
		int _components;
		TextureType _type;

	public:
		Texture2D() { }
		Texture2D(const char* name, const char* path, TextureType type = Diffuse, TextureWrapMode wrapMode = REPEAT, TextureFilterMode filterMode = LINEAR);
		~Texture2D();

	public:
		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }
		inline int GetComponentsCount() const { return _components; }

		void SetWrapMode(const TextureWrapMode wrapMode);
		void SetFilterMode(const TextureFilterMode filterMode);

		virtual void Bind() const override;
		virtual void Unbind() const override;

		friend class TextureFactory;

		static void ActivateTexture(const uint num);
		static void BindById(const id texId);

	public:
		virtual bool Load() override;
	};
}