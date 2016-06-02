#pragma once

#include <vector>
#include "BaseObject.h"

namespace s3dge
{
	class Renderer;
	class ShaderProgram;

	class Entity;
	class Camera;

	class Scene : public BaseObject
	{
	private:
		std::vector<Entity*> _entities;
		Camera* _activeCamera;
		ShaderProgram* _shaderProgram;

	public:
		Scene(ShaderProgram* shaderProgram);
		virtual ~Scene();

	public:
		const Camera*const GetActiveCamera() const { return _activeCamera; }
		const std::vector<Entity*> GetEntities() const { return _entities; }

		void SetActiveCamera(Camera*const camera);
		void AddEntity(Entity*const entity);
		void RemoveEntity(Entity*const entity);

		virtual void Update();
		virtual void Draw();

	private:
		void UpdateCamera();
	};
}