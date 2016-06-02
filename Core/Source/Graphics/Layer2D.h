/*
===========================================================================
Layer.h

A class designed to represent a layer of objects on screen.
===========================================================================
*/

#pragma once

#include <vector>
#include "../Math/Matrix4.h"

namespace s3dge
{
	class ShaderProgram;
	class Mesh;
	class Renderer2D;
	class Renderable2D;

	class Layer2D
	{
	private:
		std::vector<Renderable2D*> _renderables; // an array of elements in the layer
		ShaderProgram* _shaderProgram; // a shader instance
		Renderer2D* _renderer; // a renderer instance
		Matrix4 _transformationMatrix; // transformation applied to the layer
		bool _ownsRenderer; // flag to indicate whether the shader should be disposed by the layer upon deletion
		bool _ownsShader; // flag to indicate whether the renderer should be disposed by the layer upon deletion

	public:
		//Layer(); // TODO: needs a default shader
		Layer2D(ShaderProgram* shaderProgram);
		Layer2D(ShaderProgram* shaderProgram, Renderer2D* renderer);
		~Layer2D();

		void Add(Renderable2D* renderable);
		void Draw();

		const ShaderProgram* GetShaderProgram() const { return _shaderProgram; }
		void SetShaderProgram(ShaderProgram* shaderProgram);

		const Renderer2D* GetRenderer() const { return _renderer; }
		void SetRenderer(Renderer2D* renderer);

		const Matrix4& GetTransformationMatrix() const { return _transformationMatrix; }
		void SetTransformationMatrix(Matrix4 matrix);

		Layer2D& operator=(const Layer2D& other);

	private:
		void Dispose();
		Layer2D(const Layer2D& tRef) = delete;
	};
}