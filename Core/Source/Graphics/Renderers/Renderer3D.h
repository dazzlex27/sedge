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

#include "Renderer.h"
#include "Graphics/Structures/VertexData.h"

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
		uint _elementOffset;
		uint* _elementBuffer;
		std::vector<id> _textures; // Texture array.
		uint _textureMaxCount;

	public:
		Renderer3D();
		~Renderer3D();

		virtual void Begin() override;
		virtual void Submit(const Renderable* renderable) override;
		virtual void Flush() override; // OpenGL drawcall. 
		virtual void End() override;

	private:
		void Initialize();
		float GetTextureIndexByID(id textureID);
	};
}