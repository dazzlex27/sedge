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

	_hudLayer = new Layer2D(_shaderHUD);

	_hudLayer->Add((Label*)(GraphicsManager::GetLabel("fps")));
	_hudLayer->Add((Label*)(GraphicsManager::GetLabel("position")));

	_shaderScene->Bind();

	_shaderScene->SetUniform3f("dirLight.direction", Vector3(-1, -0.5, 1));
	_shaderScene->SetUniform3f("dirLight.ambient", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("dirLight.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("dirLight.specular", Vector3(1.0f, 1.0f, 1.0f));

	_shaderScene->SetUniform3f("pointLight.position", Vector3(2, 0.5, 0));
	_shaderScene->SetUniform3f("pointLight.ambient", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("pointLight.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("pointLight.specular", Vector3(1.0f, 1.0f, 1.0f));
	_shaderScene->SetUniform1f("pointLight.constant", 1.0f);
	_shaderScene->SetUniform1f("pointLight.linear", 0.09f);
	_shaderScene->SetUniform1f("pointLight.quadratic", 0.032f);

	_shaderScene->SetUniform3f("spotLight.direction", Vector3(0, -0.5, 1));
	_shaderScene->SetUniform3f("spotLight.ambient", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("spotLight.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("spotLight.specular", Vector3(1.0f, 1.0f, 1.0f));
	_shaderScene->SetUniform1f("spotLight.constant", 1.0f);
	_shaderScene->SetUniform1f("spotLight.linear", 0.09f);
	_shaderScene->SetUniform1f("spotLight.quadratic", 0.032f);
	_shaderScene->SetUniform1f("spotLight.inCutOff", (float)cos(0.226893));
	_shaderScene->SetUniform1f("spotLight.outCutOff", (float)cos(0.314159));
}

void Application::Update()
{
	Vector3 cameraPosition = _camera->GetPosition();
	UpdateCamera(*_camera, cameraPosition, InputManager::GetMouseDisplacement());

	_shaderScene->Bind(); 
	_shaderScene->SetUniform3f("spotLight.position", _camera->GetPosition());
	_shaderScene->SetUniform3f("spotLight.direction", _camera->GetViewDirection());

	GraphicsManager::GetLabel("fps")->SetText(std::to_string(GetFPS()) + " fps");
	GraphicsManager::GetLabel("position")->SetText(std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z));

	_mainScene->Update();
	_shaderScene->SetUniform3f("viewPos", cameraPosition);
}

void Application::Render()
{
	_shaderScene->Bind();
	_shaderScene->SetUniform1i("material.diffuse", 0);
	_shaderScene->SetUniform1i("material.specular", 1);
	_shaderScene->SetUniform1f("material.shininess", 32.0f);
	_shaderScene->SetModel(Matrix4::GetIdentity());
	Texture2D::ActivateTexture(0);
	TextureManager::Get("cry")->Bind();
	Texture2D::ActivateTexture(1);
	TextureManager::Get("lm-test-sp")->Bind();
	GraphicsManager::GetMesh("cube")->Draw();
	_shaderScene->SetModel(Matrix4::GetTranslation(Vector3(-2, 0, 0)));
	GraphicsManager::GetMesh("cube")->Draw();
	_shaderScene->SetModel(Matrix4::GetRotation(Vector3(0, 1, 0), 35) * Matrix4::GetTranslation(Vector3(-1, 1, 0)));
	GraphicsManager::GetMesh("cube")->Draw();
	_shaderScene->SetModel(Matrix4::GetRotation(Vector3(1, 0, 0), 25) * Matrix4::GetTranslation(Vector3(0, 1, -1)));
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