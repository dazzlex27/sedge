/*
===========================================================================
Skybox.h

Declares the Skybox class, made for rendering cubic skybox textures.
===========================================================================
*/

#pragma once

#include "Renderable3D.h"

namespace s3dge
{
	class VertexBuffer;
	class IndexBuffer;
	class Cubemap;

	class Skybox : public Renderable3D
	{
	private:
		VertexBuffer* _vbo;
		IndexBuffer* _ibo;
		Cubemap* _texture;

	private:
		Skybox(Cubemap*const texture);

	public:
		virtual void Draw() const override;

		friend class SkyboxFactory;
	};
}