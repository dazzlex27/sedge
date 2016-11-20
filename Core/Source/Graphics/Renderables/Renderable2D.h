#pragma once

#include "Maths/MathsHeader.h"
#include "Graphics/Textures/Texture.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Internal/DeleteMacros.h"
#include "Utilities/Converters.h"
#include "Graphics/Renderer2DBase.h"
#include "Graphics/GraphicsStructures.h"

namespace s3dge
{
	namespace Graphics
	{
		class Renderable2D
		{
		protected:
			Maths::vec3f _position;
			Maths::vec2f _size;
			uint _color;
			std::vector<Maths::vec2f> _uv;
			Texture* _texture;

		protected:
			Renderable2D()
				: _texture(nullptr)
			{
				SetDefaultUVConfiguration();
			}

			Renderable2D(const Maths::vec3f& position, const Maths::vec2f& size, uint color)
				: _position(position), _size(size), _color(color), _texture(nullptr)
			{
				SetDefaultUVConfiguration();
			}

		public:
			virtual ~Renderable2D() 
			{
			}

			virtual void Submit(Renderer2DBase* renderer) const
			{
				renderer->Submit(this);
			}

		public:
			inline const Maths::vec3f GetPosition() const { return _position; }
			inline const Maths::vec2f GetSize() const { return _size; }
			inline uint GetColor() const { return _color; }
			inline std::vector<Maths::vec2f> GetUV() const { return _uv; }
			inline uint GetTextureID() const { return _texture ? _texture->GetTextureID() : 0; }

			inline void SetColor(uint color) { _color = color; }
			inline void SetColor(const Maths::vec4f& color) { _color = ConvertColorToUint(color); }

		private:
			void SetDefaultUVConfiguration()
			{
				_uv.push_back(Maths::vec2f(0, 0));
				_uv.push_back(Maths::vec2f(0, 1));
				_uv.push_back(Maths::vec2f(1, 1));
				_uv.push_back(Maths::vec2f(1, 0));
			}
		};
	}
}