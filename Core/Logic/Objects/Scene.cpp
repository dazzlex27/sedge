/*
===========================================================================
Scene.cpp

Implements the Scene class
===========================================================================
*/

#include "Scene.h"
#include "Entity.h"
#include "Logic/Cameras/Camera.h"
#include "System/MemoryManagement.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Terrain/Terrain.h"
#include "Graphics/Renderables/Skybox.h"
#include "Graphics/GraphicsAPI.h"

using namespace s3dge;

Scene::Scene(Camera*const camera, ShaderProgram*const mainShader)
{
	_camera = camera;
	_mainShader = mainShader;
}

void Scene::AddEntity(Entity*const entity)
{
	_entities.push_back(entity);
}

void Scene::RemoveEntity(Entity*const entity)
{
}

void Scene::Update()
{
	UpdateCamera();

	const Vector3& cameraPosition = _camera->GetPosition();
	const Vector3& cameraDirection = _camera->GetViewDirection();

	_mainShader->Bind();
	_mainShader->SetUniform3f("spotLight.position", cameraPosition);
	_mainShader->SetUniform3f("spotLight.direction", _camera->GetViewDirection());
	_mainShader->SetUniform3f("viewPos", cameraPosition);
}

void Scene::Draw()
{
	const Matrix4& projection = _camera->GetProjection();
	const Matrix4& view = _camera->GetView();

	_shaderTerrain->Bind();
	_shaderTerrain->SetProjection(projection);
	_shaderTerrain->SetView(view);
	_terrain->Draw();

	_shaderSkybox->Bind();
	_shaderSkybox->SetProjection(projection);
	_shaderSkybox->SetView(view);
	GraphicsAPI::DisableDepthMask();
	_skybox->Draw();
	GraphicsAPI::EnableDepthMask();

	_mainShader->Bind();
	_mainShader->SetProjection(projection);
	_mainShader->SetView(view);

	for (uint i = 0; i < _entities.size(); i++)
	{
		_mainShader->SetModel(_entities[i]->GetModelMatrix());
		_entities[i]->Draw();
	}
}

void Scene::SetCamera(Camera*const camera)
{
	if (_camera)
		SafeDelete(_camera);

	_camera = camera;
}

void Scene::SetSkybox(Skybox*const skybox, ShaderProgram*const shaderSkybox)
{
	if (_skybox)
		SafeDelete(_skybox);

	if (_shaderSkybox)
		SafeDelete(_shaderSkybox);

	_skybox = skybox;
	_shaderSkybox = shaderSkybox;
}

void Scene::SetTerrain(Terrain*const terrain, ShaderProgram*const shaderTerrain)
{
	if (_terrain)
		SafeDelete(_terrain);

	if (_shaderTerrain)
		SafeDelete(_shaderTerrain);

	_terrain = terrain;
	_shaderTerrain = shaderTerrain;
}

void Scene::UpdateCamera()
{
	if (!_camera)
		return;

	_mainShader->Bind();
	_mainShader->SetProjection(_camera->GetProjection());
	_mainShader->SetView(_camera->GetView());
}

Scene::~Scene()
{
	SafeDelete(_camera);
	SafeDelete(_shaderTerrain);
	SafeDelete(_shaderSkybox);
	SafeDelete(_skybox);
	SafeDelete(_terrain);
	SafeDelete(_mainShader);

	for (auto entity : _entities)
		SafeDelete(entity);
}