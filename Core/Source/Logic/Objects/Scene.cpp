#include "Scene.h"
#include "Entity.h"
#include "Logic/Cameras/Camera.h"
#include "Graphics/Renderers/RendererBF.h"
#include "Internal/DeleteMacros.h"
#include "Graphics/Shaders/ShaderProgram.h"

using namespace s3dge;
using namespace graphics;

Scene::Scene(ShaderProgram* shaderProgram)
{
	_shaderProgram = shaderProgram;
}

void Scene::AddEntity(Entity* entity)
{
	_entities.push_back(entity);
}

void Scene::Update()
{

	UpdateCamera();
}

void Scene::Render()
{
	for (uint i = 0; i < _entities.size(); i++)
	{
		_shaderProgram->SetModel(_entities[i]->GetModelMatrix());
		_entities[i]->Render();
	}
}

void Scene::SetActiveCamera(Camera* camera)
{
	_activeCamera = camera;
	UpdateCamera();
}

void Scene::UpdateCamera()
{
	if (_activeCamera == nullptr)
		return;

	_shaderProgram->SetProjection(_activeCamera->GetProjection());
	_shaderProgram->SetView(_activeCamera->GetView());
}

Scene::~Scene()
{
	SafeDelete(_shaderProgram);
}