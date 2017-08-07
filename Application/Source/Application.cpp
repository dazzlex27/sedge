#include "Application.h"
#include <cmath>
#include "Logic.h"
#include "UpdateLogic.h"

using namespace s3dge;

void Application::Initialize()
{
	CreateGameWindow("S3DGE Application", 1280, 720, false, false);

	_shaderScene = new ShaderProgram("Resources/Shaders/basic.vert", "Resources/Shaders/light.frag");
	_shaderHUD = new ShaderProgram("Resources/Shaders/basic.vert", "Resources/Shaders/static.frag");
	
	_camera = new FPSCamera();
	_camera->SetPosition(Vector3(0, 1.5, 4));

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderHUD->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	
	LoadResources();
	CreateRenderables();

	Actor* cube = new Actor(GraphicsManager::GetMesh("cube"));
	cube->SetPosition(Vector3(-0.5f, 0.3f, 0.5f));

	_mainScene = new Scene(_shaderScene);
	_mainScene->AddEntity(cube);
	_mainScene->SetActiveCamera(_camera);

	_hudLayer = new Layer(_shaderHUD);

	_hudLayer->Add(GraphicsManager::GetLabel("fps"));
	_hudLayer->Add(GraphicsManager::GetLabel("position"));

	_shaderScene->Bind();
	_shaderScene->SetUniform3f("light.direction", Vector3(0, -0.5, 1));
	_shaderScene->SetUniform1f("light.constant", 1.0f);
	_shaderScene->SetUniform1f("light.linear", 0.09f);
	_shaderScene->SetUniform1f("light.quadratic", 0.032f);
}

void Application::Update()
{
	Vector3 cameraPosition = _camera->GetPosition();
	UpdateCamera(*_camera, cameraPosition, InputManager::GetMouseDisplacement());

	_shaderScene->Bind(); 
	_shaderScene->SetUniform3f("light.position", _camera->GetPosition());
	_shaderScene->SetUniform3f("light.direction", _camera->GetViewDirection());
	_shaderScene->SetUniform1f("light.inCutOff", cos(0.226893));
	_shaderScene->SetUniform1f("light.outCutOff", cos(0.314159));

	GraphicsManager::GetLabel("fps")->SetText(std::to_string(GetFPS()) + " fps");
	GraphicsManager::GetLabel("position")->SetText(std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z));

	_mainScene->Update();
	_shaderScene->SetUniform3f("viewPos", cameraPosition);
}

void Application::Render()
{
	_shaderScene->Bind();
	_shaderScene->SetModel(Matrix4::GetIdentity());
	_shaderScene->SetUniform3f("light.ambient", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("light.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("light.specular", Vector3(1.0f, 1.0f, 1.0f));
	_shaderScene->SetUniform1i("material.diffuse", 0);
	_shaderScene->SetUniform1i("material.specular", 1);
	_shaderScene->SetUniform1f("material.shininess", 32.0f);
	Texture2D::ActivateTexture(0);
	TextureManager::Get("lm-test")->Bind();
	Texture2D::ActivateTexture(1);
	TextureManager::Get("lm-test-sp")->Bind();
	GraphicsManager::GetMesh("cube")->Draw();
	_shaderScene->SetModel(Matrix4::Translate(Vector3(-2, 0, 0)));
	GraphicsManager::GetMesh("cube")->Draw();
	_shaderScene->SetModel(Matrix4::Rotate(Vector3(0, 1, 0), 35) * Matrix4::Translate(Vector3(-1, 1, 0)));
	GraphicsManager::GetMesh("cube")->Draw();
	_shaderScene->SetModel(Matrix4::Rotate(Vector3(1, 0, 0), 25) * Matrix4::Translate(Vector3(0, 1, -1)));
	GraphicsManager::GetMesh("cube")->Draw();
	_hudLayer->Draw();
}

void Application::Dispose()
{
	SafeDelete(_mainScene);
	SafeDelete(_hudLayer);
	SafeDelete(_shaderHUD);
	SafeDelete(_camera);
}