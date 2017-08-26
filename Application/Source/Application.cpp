#include "Application.h"

using namespace s3dge;

static void UpdateCamera(Camera& camera, const Vector3& position, const Vector2& displacement);

void Application::Initialize()
{
	CreateGameWindow("S3DGE Application", 1280, 720, false, false);

	_shaderScene = new ShaderProgram("Resources/Shaders/basic.vert", "Resources/Shaders/light.frag");
	_shaderHUD = new ShaderProgram("Resources/Shaders/basic.vert", "Resources/Shaders/static.frag");
	
	_camera = new FPSCamera();
	_camera->SetPosition(Vector3(0, 1.5, 4));

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderHUD->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	
	TextureManager::Add("cry", "Resources/Models/nanosuit/body_dif.png");
	TextureManager::Add("lm-test", "Resources/Textures/lm-test.png");
	TextureManager::Add("lm-test-sp", "Resources/Textures/lm-test-sp.png");
	FontManager::Add("font1", "Resources/Fonts/Assistant-Regular.ttf", 24);

	Renderable3DManager::AddModel("nano", ModelUtils::ReadFromFile("Resources/Models/nanosuit/nanosuit.obj"));

	Label* label = LabelFactory::CreateLabel("startup...", FontManager::Get("font1"), Vector2(0.3f, 8.4f), 0, Size2D(2, 2));
	Label* label2 = LabelFactory::CreateLabel("p:", FontManager::Get("font1"), Vector2(0.3f, 7.8f), 0, Size2D(2, 2));

	Renderable3DManager::AddMesh("cube", MeshFactory::CreateCubeOfUnitSize(nullptr));
	Renderable2DManager::AddLabel("fps", label);
	Renderable2DManager::AddLabel("position", label2);

	Actor* cube = new Actor(Renderable3DManager::GetMesh("cube"));
	cube->SetPosition(Vector3(-0.5f, 0.3f, 0.5f));

	_mainScene = new Scene(_shaderScene);
	_mainScene->AddEntity(cube);
	_mainScene->SetActiveCamera(_camera);

	_hudLayer = new Layer2D(_shaderHUD);

	_hudLayer->Add((Label*)(Renderable2DManager::GetLabel("fps")));
	_hudLayer->Add((Label*)(Renderable2DManager::GetLabel("position")));

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

	Renderable2DManager::GetLabel("fps")->SetText(std::to_string(GetFPS()) + " fps");
	Renderable2DManager::GetLabel("position")->SetText(std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z));

	_mainScene->Update();
	_shaderScene->SetUniform3f("viewPos", cameraPosition);
}

void Application::Render()
{
	_shaderScene->Bind();
	_shaderScene->SetUniform1i("material.diffuse", 0);
	_shaderScene->SetUniform1i("material.specular", 1);
	_shaderScene->SetUniform1f("material.shininess", 32.0f);
	Renderable3DManager::GetModel("nano")->Draw();
	_hudLayer->Draw();
}

void Application::Dispose()
{
	SafeDelete(_mainScene);
	SafeDelete(_hudLayer);
	SafeDelete(_shaderHUD);
	SafeDelete(_camera);
}

float horizontalAngle = 0;
float verticalAngle = 0;

void UpdateCamera(Camera& camera, const Vector3& position, const Vector2& displacement)
{
	const float speed = 0.1f;
	const float mouseSpeed = 3.0f;

	Vector3 cameraPosition(position);

	horizontalAngle += mouseSpeed * displacement.x;
	verticalAngle -= mouseSpeed * displacement.y;

	if (verticalAngle > 1.57f)
		verticalAngle = 1.57f;
	if (verticalAngle < -1.57f)
		verticalAngle = -1.57f;

	Vector3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), -cos(verticalAngle) * cos(horizontalAngle));
	Vector3 right(-(float)sin(horizontalAngle - 3.14 / 2.0f), 0, (float)cos(horizontalAngle - 3.14 / 2.0f));
	Vector3 up((Vector3::GetCrossProduct(right, direction)));

	if (InputManager::KeyDown(S3_KEY_W))
		cameraPosition += speed * direction;
	if (InputManager::KeyDown(S3_KEY_S))
		cameraPosition -= speed * direction;
	if (InputManager::KeyDown(S3_KEY_A))
		cameraPosition -= speed * right;
	if (InputManager::KeyDown(S3_KEY_D))
		cameraPosition += speed * right;
	if (InputManager::KeyDown(S3_KEY_Q))
		cameraPosition -= speed * up;
	if (InputManager::KeyDown(S3_KEY_E))
		cameraPosition += speed * up;
	if (InputManager::KeyDown(S3_KEY_SPACE))
	{
		horizontalAngle = 0;
		verticalAngle = 0;
	}
	if (InputManager::KeyDown(S3_KEY_MWUP))
		camera.SetFOV(camera.GetFOV() - 1);
	if (InputManager::KeyDown(S3_KEY_MWDOWN))
		camera.SetFOV(camera.GetFOV() + 1);
	if (InputManager::KeyDown(S3_KEY_MMB))
		camera.SetFOV(45);

	camera.SetPosition(cameraPosition);
	camera.SetViewDirection(direction);
	camera.SetUp(up);
}
