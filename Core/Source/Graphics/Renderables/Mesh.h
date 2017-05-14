/*
===========================================================================
Mesh.h

Declares the Mesh class
===========================================================================
*/

#pragma once

#include "Renderable.h"
#include "Math/Vector3.h"
#include "Graphics/Structures/Color.h"

namespace s3dge
{
	class VertexArray;
	class VertexBuffer;
	class ElementBuffer;
	class Renderer2D;
	class Texture2D;
	class Renderer;
	class VertexLayout;

	class Mesh : public Renderable
	{
	private:
		VertexArray* _vao;
		VertexBuffer* _vbo;
		ElementBuffer* _ibo;

	public:
		Vector3 translation;
		Vector3 scale;
		Texture2D* texture;

	private:
		Mesh(VertexBuffer* vbo, ElementBuffer* ibo);
		Mesh(VertexBuffer* vbo, ElementBuffer* ibo, Texture2D* texture);

	public:
		~Mesh();

	public:
		VertexArray* GetVAO() const { return _vao; }
		ElementBuffer* GetIBO() const { return _ibo; }

		void Submit(Renderer* renderer) const;
		void Render() const override;

	private:
		VertexLayout GetDefaultVertexLayout();

		friend class MeshFactory;
	};
}