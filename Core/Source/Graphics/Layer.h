#pragma once

#include <vector>
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Graphics/Shaders/ShaderProgram.h"

namespace s3dge
{
	namespace Graphics
	{
		class Layer
		{
		private:
			std::vector<Renderable2D*> _renderables;
			ShaderProgram* _shaderProgram;
			Renderer2D* _renderer;
			Maths::mat4 _transformationMatrix;
			bool _ownsRenderer;
			bool _ownsShader;

		public:
			//Layer(); // TODO: needs a default shader
			Layer(ShaderProgram* shaderProgram);
			Layer(ShaderProgram* shaderProgram, Renderer2D* renderer);
			~Layer();

			void Add(Renderable2D* renderable);
			void Render();

			const ShaderProgram* GetShaderProgram() const { return _shaderProgram; }
			void SetShaderProgram(ShaderProgram* shaderProgram);

			const Renderer2D* GetRenderer() const { return _renderer; }
			void SetRenderer(Renderer2D* renderer);

			const Maths::mat4& GetTransformationMatrix() const { return _transformationMatrix; }
			void SetTransformationMatrix(Maths::mat4 matrix);

			Layer& operator=(const Layer& other);

		private:
			void Dispose();
			Layer(const Layer& tRef) = delete;
		};
	}
}