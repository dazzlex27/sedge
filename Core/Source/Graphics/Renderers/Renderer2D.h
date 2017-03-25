#pragma once

#include <vector>
#include <string>

#include "Graphics/Structures/VertexData.h"

namespace s3dge
{
	namespace graphics
	{
		class Mesh2D;
		class Renderable2D;
		class VertexArray;
		class VertexBuffer;
		class IndexBuffer;
		class Font;
		struct Color;

		class Renderer2D
		{
		private:
			VertexArray* _vao; // Vertex array object.
			VertexBuffer* _vbo; // Vertex buffer object.
			IndexBuffer* _ibo; // Index buffer object.
			int _indexCount; // The number of indices.
			VertexData* _buffer; // Renderables container.
			std::vector<id> _textures; // Texture array.
			std::vector<Mesh2D*> _meshes;

		public:
			Renderer2D();	
			~Renderer2D();

			void Begin();
			void Submit(const Renderable2D* renderable);
			void SubmitMesh(Mesh2D* mesh);
			void Flush(); // OpenGL drawcall. 
			void End();

			void DrawString(const std::string& text, Font* font, const Point3D& position, const Color& color);

		private:
			void Initialize();
			float GetTextureSlotByID(id textureID);
		};
	}
}