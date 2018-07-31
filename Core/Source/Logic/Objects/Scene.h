#pragma once

#include <vector>
#include "BaseObject.h"

namespace s3dge
{
	class Renderer;
	class ShaderProgram;
	struct Matrix4;

	class Entity;
	class Camera;
	class Skybox;
	class Terrain;

	class Scene : public BaseObject
	{
	private:
		std::vector<Entity*> _entities;
		Camera* _camera;
		ShaderProgram* _mainShader;
		ShaderProgram* _shaderSkybox;
		ShaderProgram* _shaderTerrain;
		Skybox* _skybox;
		Terrain* _terrain;

	public:
		Scene(Camera*const camera, ShaderProgram*const mainShader);
		virtual ~Scene();

	public:
		Camera*const GetCamera() const { return _camera; }
		const Skybox*const GetSkybox() const { return _skybox; }
		const Terrain*const GetTerrain() const { return _terrain; }
		const std::vector<Entity*> GetEntities() const { return _entities; }

		void SetCamera(Camera*const camera);
		void SetSkybox(Skybox*const skybox, ShaderProgram*const shaderSkybox);
		void SetTerrain(Terrain*const terrain, ShaderProgram*const shaderTerrain);
		void AddEntity(Entity*const entity);
		void RemoveEntity(Entity*const entity);

		virtual void Update();
		virtual void Draw();

	private:
		void UpdateCamera();
	};
}