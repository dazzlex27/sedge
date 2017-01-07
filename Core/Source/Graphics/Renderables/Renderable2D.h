/*
===========================================================================
Renderable2D.h

Base class for all 2D renderable objects.
===========================================================================
*/

#pragma once

#include "Maths/MathsHeader.h"
#include "Graphics/Textures/Texture.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Renderers/Renderer2DBase.h"

namespace s3dge
{
	namespace graphics
	{
		class Renderable2D
		{
		protected:
			maths::vec3f _position;
			maths::vec2f _size;
			uint _color;
			std::vector<maths::vec2f> _uv;
			Texture* _texture;

		protected:
			Renderable2D();
			Renderable2D(const maths::vec3f& position, const maths::vec2f& size, uint color);

		public:
			virtual ~Renderable2D();
			virtual void Submit(Renderer2DBase* renderer) const;

		public:
			inline const maths::vec3f GetPosition() const { return _position; }
			inline const maths::vec2f GetSize() const { return _size; }
			inline uint GetColor() const { return _color; }
			inline std::vector<maths::vec2f> GetUV() const { return _uv; }
			inline uint GetTextureID() const { return _texture ? _texture->GetID() : 0; }

			void SetColor(uint color);
			void SetColor(const maths::vec4f& color);

		private:
			void SetDefaultUVConfiguration();
		};
	}
}