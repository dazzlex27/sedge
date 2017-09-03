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
	class VertexArray;
	class VertexBuffer;
	class ElementBuffer;
	class Cubemap;

	class Skybox : public Renderable3D
	{
	private:
		VertexArray* _vao;
		VertexBuffer* _vbo;
		ElementBuffer* _ebo;
		Cubemap* _texture;

	private:
		Skybox(Cubemap*const texture);

	public:
		virtual void Draw() const override;

		friend class SkyboxFactory;
	};
}