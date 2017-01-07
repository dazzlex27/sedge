#pragma once

#include <GL/glew.h>
#include <freetype-gl.h>
#include "Graphics/Renderers/Renderer2DBase.h"
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/GraphicsStructures.h"
#include "Platforms/Window.h"

namespace s3dge
{
	namespace graphics
	{
		#define RENDERER_MAX_SPRITES	60000
		#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
		#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
		#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
		#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

		class Renderer2D : public Renderer2DBase
		{
		private:
			uint _vao; // Vertex array object.
			uint _vbo; // Vertex buffer object.
			IndexBuffer* _ibo; // Index buffer object.
			int _indexCount; // The number of indices.
			VertexData* _buffer; // Renderables container.
			std::vector<uint> _textures; // Texture array.
			const Window* _window;

		public:
			Renderer2D(const Window* window);	
			~Renderer2D();

			void Begin() override;
			void Submit(const Renderable2D* renderable) override;
			void Flush() override; // OpenGL drawcall. 
			void End() override;

			void DrawString(const std::string& text, Font* font, const maths::vec3f& position, uint color) override;

		private:
			void Initialize();
		};
	}
}