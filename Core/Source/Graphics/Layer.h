/*
===========================================================================
Layer.h

A class designed to represent a layer of objects on screen.
Each layer requires a shader instance and a renderer instance.
In case a renderer is not specified, a local one will be created.
TODO: In case a shader is not specified, a default one will be used.

Using layers is highly encouraged, even if there's only one. That helps to keep things clean.
===========================================================================
*/

#pragma once

#include <vector>
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Graphics/Shaders/ShaderProgram.h"

namespace s3dge
{
	namespace graphics
	{
		class Layer
		{
		private:
			std::vector<Renderable2D*> _renderables; // an array of elements in the layer
			ShaderProgram* _shaderProgram; // a shader instance
			Renderer2D* _renderer; // a renderer instance
			maths::mat4 _transformationMatrix; // transformation applied to the layer
			bool _ownsRenderer; // flag to indicate whether the shader should be disposed by the layer upon deletion
			bool _ownsShader; // flag to indicate whether the renderer should be disposed by the layer upon deletion

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

			const maths::mat4& GetTransformationMatrix() const { return _transformationMatrix; }
			void SetTransformationMatrix(maths::mat4 matrix);

			Layer& operator=(const Layer& other);

		private:
			void Dispose();
			Layer(const Layer& tRef) = delete;
		};
	}
}