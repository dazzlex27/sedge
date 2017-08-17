#pragma once

#include <vector>
#include "CustomTypes.h"

namespace s3dge
{
	class VertexArray;
	class VertexBuffer;
	class ElementBuffer;
	class VertexDataS;

	class Renderable2D;
	class Label;
	class Font;
	struct Color;
	struct Vector3;

	class Renderer2D
	{
	private:
		VertexArray* _vao;
		VertexBuffer* _vbo;
		ElementBuffer* _ebo;

		VertexDataS* _buffer;
		uint _elementCount;

		std::vector<uint> _textureIDs;

		const uint _maxVertices;

	public:
		Renderer2D(const uint maxVertices = 100000);
		~Renderer2D();

		void Begin();
		void Submit(const Renderable2D& sprite);
		void RenderText(const char* text, const Font& font, const Vector3& position, const Color& color);
		void End();
		void Flush();

	private:
		const float GetSamplerIndexByTID(const id texID);
	};
}