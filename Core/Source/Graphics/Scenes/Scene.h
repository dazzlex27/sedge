/*
===========================================================================
Scene.h

A class to represent a game scene (level) which is responsible for managing the entities it contains
(like actors, cameras, items, etc.)
===========================================================================
*/

#pragma once

#include <vector>

namespace s3dge
{
	class Entity;
	class Camera;

	class Scene
	{
	private:
		std::vector<Entity*> _entities;
		Camera* _camera;

	public:
		Scene();
		~Scene();

		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);

		void SetCamera(Camera* camera);

		void Update();
		void Render();
	};
}