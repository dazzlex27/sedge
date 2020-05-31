/*
===========================================================================
Renderer2D.h

This renderer is a batch renderer designed to deal with quad objects.
TODO: make this an instanced renderer.
===========================================================================
*/

#pragma once

#include <vector>
#include <CustomTypes.h>

namespace sedge
{
	class VertexBuffer;
	class IndexBuffer;
	struct VertexDataS;

	class Renderable2D;
	class Label;
	class Font;
	struct Color;
	struct Vector3;

	class Renderer2D
	{
	private:
		VertexBuffer* _vbo;
		IndexBuffer* _ibo;

		VertexDataS* _buffer;
		uint _indexCount;

		std::vector<uint> _textureIDs;

		const uint _maxVertices;

	public:
		Renderer2D(const uint maxVertices = 100000);
		~Renderer2D();

		void Begin();
		void Submit(const Renderable2D*const sprite);
		void RenderText(const char* text, const Font*const font, const Vector3& position, const Color& color);
		void End();
		void Flush();

	private:
		const float GetSamplerIndexByTID(const ID texID);
	};
}