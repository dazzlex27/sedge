/*
===========================================================================
Renderable2D.h

Base class for all 2D renderable objects.
===========================================================================
*/

#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Graphics/Textures/Texture2D.h"

namespace s3dge
{
	namespace graphics
	{
		class Renderable2D
		{
		protected:
			math::vec3f _position;
			math::vec2f _size;
			uint _color;
			std::vector<math::vec2f> _uv;
			Texture2D* _texture;

		protected:
			Renderable2D();
			Renderable2D(const math::vec3f& position, const math::vec2f& size, uint color);

		public:
			virtual ~Renderable2D();
			virtual void Submit(Renderer2D* renderer) const;

		public:
			inline virtual const math::vec3f GetPosition() const { return _position; }
			inline const math::vec2f GetSize() const { return _size; }
			inline uint GetColor() const { return _color; }
			inline std::vector<math::vec2f> GetUV() const { return _uv; }
			inline uint GetTextureID() const { return _texture ? _texture->GetID() : 0; }

			void SetColor(uint color);
			void SetColor(const math::vec4f& color);

		private:
			void SetDefaultUVConfiguration();
		};
	}
}