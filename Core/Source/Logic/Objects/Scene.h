#pragma once

#include <vector>
#include "BaseObject.h"

namespace s3dge
{
	namespace graphics
	{
		class Renderer;
		class ShaderProgram;
	}

	class Entity;
	class Camera;

	class Scene : public BaseObject
	{
	private:
		std::vector<Entity*> _entities;
		Camera* _activeCamera;
		graphics::ShaderProgram* _shaderProgram;

	public:
		Scene(graphics::ShaderProgram* shaderProgram);
		virtual ~Scene();

	public:
		const Camera* GetActiveCamera() const { return _activeCamera; }
		const std::vector<Entity*> GetEntities() const { return _entities; }

		void SetActiveCamera(Camera* camera);
		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);

		virtual void Update();
		virtual void Render();

	private:
		void UpdateCamera();
	};
}