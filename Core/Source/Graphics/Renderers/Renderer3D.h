/*
===========================================================================
Renderer3D.h

Declares the Renderer3D class.
This renderer is a general purpose batch renderer. 
Takes plain Renderable objects and piles them up in a single buffer.
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
	class VertexArray;
	class VertexBuffer;
	class ElementBuffer;
	class Font;
	struct Color;

	class Renderer3D : public Renderer
	{
	private:
		VertexArray* _vao; // Vertex array object.
		VertexBuffer* _vbo; // Vertex buffer object.
		ElementBuffer* _ebo; // Index buffer object.
		uint _elementCount; // The number of indices.
		VertexData* _vertexBuffer; // Renderables container.
		uint* _elementBuffer;
		std::vector<id> _textures; // Texture array.

	public:
		Renderer3D();
		~Renderer3D();

		virtual void Begin() override;
		virtual void Submit(const Renderable* renderable) override;
		virtual void Flush() override; // OpenGL drawcall. 
		virtual void End() override;

		//void DrawString(const std::string& text, Font* font, const Point3D& position, const Color& color);

	private:
		void Initialize();
		//float GetTextureSlotByID(id textureID);
	};
}