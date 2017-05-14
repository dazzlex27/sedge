/*
===========================================================================
Renderer2D.h

Declares the Renderer2D class.
===========================================================================
*/

#pragma once

#include <vector>
#include <string>

#include "Graphics/Structures/VertexData.h"
#include "Renderer.h"

namespace s3dge
{
	class Mesh;
	class Renderable2D;
	class VertexArray;
	class VertexBuffer;
	class ElementBuffer;
	class Font;
	struct Color;

	class Renderer2D : public Renderer
	{
	private:
		VertexArray* _vao; // Vertex array object.
		VertexBuffer* _vbo; // Vertex buffer object.
		ElementBuffer* _ibo; // Index buffer object.
		int _indexCount; // The number of indices.
		VertexData* _buffer; // Renderables container.
		std::vector<id> _textures; // Texture array.
		std::vector<const Mesh*> _meshes;

	public:
		Renderer2D();
		~Renderer2D();

		virtual void Begin() override;
		virtual void Submit(const Renderable2D* renderable);
		virtual void SubmitMesh(const Mesh* mesh) override;
		virtual void Flush() override; // OpenGL drawcall. 
		virtual void End() override;

		void DrawString(const std::string& text, Font* font, const Point3D& position, const Color& color);

	private:
		void Initialize();
		float GetTextureSlotByID(id textureID);
	};
}