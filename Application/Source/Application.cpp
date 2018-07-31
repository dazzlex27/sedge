#include "Application.h"

using namespace std;
using namespace s3dge;

static void UpdateCamera(Camera& camera, const InputManager& inputManager);
static void SetLightingParameters(ShaderProgram*const shaderScene);

void Application::LoadAssets()
{
	_fontManager->AddFont("font1", "Resources/Fonts/Assistant-Regular.ttf", 14);
	_textureManager->AddTex2D("lm-test", "Resources/Textures/lm-test.png");
	_textureManager->AddTex2D("lm-test-sp", "Resources/Textures/lm-test-sp.png");
	_textureManager->AddTex2D("terrain", "Resources/Textures/forrest-terrain.jpg");

	vector<string> sb_paths;
	sb_paths.push_back("Resources/Textures/sb/sb_rt.png");
	sb_paths.push_back("Resources/Textures/sb/sb_lt.png");
	sb_paths.push_back("Resources/Textures/sb/sb_tp.png");
	sb_paths.push_back("Resources/Textures/sb/sb_bt.png");
	sb_paths.push_back("Resources/Textures/sb/sb_bk.png");
	sb_paths.push_back("Resources/Textures/sb/sb_ft.png");
	_textureManager->AddCubemap("skybox", sb_paths);
}

Application::Application()
{
	_fontManager = new FontManager();
	_shaderFactory = new ShaderFactory();
	_textureManager = new TextureManager();
	_renderable2DManager = new Renderable2DManager();
}

Application::~Application()
{
	SafeDelete(_fontManager);
	SafeDelete(_shaderFactory);
	SafeDelete(_textureManager);
	SafeDelete(_renderable2DManager);
}

void Application::Initialize(const InitializationToolset& initToolset)
{
	_graphicsObjFactorySet = initToolset.GraphicsObjFactorySet;

	CreateGameWindow("S3DGE Application", 1280, 720, false, false);

	_inputManager = MainWindow->GetInputManager();

	LoadAssets();

	auto terrain = new Terrain(_textureManager->GetTex2D("terrain"));
	auto terrainShader = _shaderFactory->CreateShaderProgram("terrain", "Resources/Shaders/terrain.vert", "Resources/Shaders/terrain.frag");

	auto skybox = new Skybox(_textureManager->GetCubemap("skybox"));
	auto shaderSkybox = _shaderFactory->CreateShaderProgram("skybox", "Resources/Shaders/skybox.vert", "Resources/Shaders/skybox.frag");

	auto camera = new FPSCamera();
	camera->SetPosition(Vector3(0, 1, 0));

	//auto sponzaModel = _graphicsObjFactorySet.ModelFactory.CreateModel("Resources/Models/sponza/sponza.obj");
	//auto sponza = new Actor(sponzaModel);
	//sponza->SetScale(Vector3(0.008f, 0.008f, 0.008f));

	auto nanosuitModel = _graphicsObjFactorySet.ModelFactory.CreateModel("Resources/Models/nanosuit/nanosuit.obj");
	auto nano = new Actor(nanosuitModel);
	nano->SetPosition(Vector3(0, 0, -1.5f));
	nano->SetScale(Vector3(0.1f, 0.1f, 0.1f));

	auto cubeMesh = new Cube(0xff00ff);
	auto cube = new Actor(cubeMesh);

	auto shaderScene = _shaderFactory->CreateShaderProgram("scene", "Resources/Shaders/scene.vert", "Resources/Shaders/scene.frag");
	_mainScene = new Scene(camera, shaderScene);
	_mainScene->SetTerrain(terrain, terrainShader);
	_mainScene->SetSkybox(skybox, shaderSkybox);
	//_mainScene->AddEntity(sponza);
	_mainScene->AddEntity(nano);
	_mainScene->AddEntity(cube);
	SetLightingParameters(shaderScene);

	auto label = _graphicsObjFactorySet.LabelFactory.CreateLabel("startup...", _fontManager->GetFont("font1"), Vector2(0.1f, 8.7f), 0, Size2D(2, 2));
	auto label2 = _graphicsObjFactorySet.LabelFactory.CreateLabel("p:", _fontManager->GetFont("font1"), Vector2(0.1f, 8.4f), 0, Size2D(2, 2));

	_renderable2DManager->AddLabel("fps", label);
	_renderable2DManager->AddLabel("position", label2);

	auto shaderHud = _shaderFactory->CreateShaderProgram("hud", "Resources/Shaders/hud.vert", "Resources/Shaders/hud.frag");
	shaderHud->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	_hudLayer = new Layer2D(shaderHud);
	_hudLayer->Add(label);
	_hudLayer->Add(label2);
}

void Application::UpdateLogic()
{
	Camera* camera = _mainScene->GetCamera();
	UpdateCamera(*camera, *_inputManager);

	_mainScene->Update();

	const Vector3& cameraPosition = camera->GetPosition();
	_renderable2DManager->GetLabel("fps")->SetText(std::to_string(GetFPS()) + " fps");
	auto posX = std::to_string(cameraPosition.x);
	auto posY = std::to_string(cameraPosition.y);
	auto posZ = std::to_string(cameraPosition.z);
	_renderable2DManager->GetLabel("position")->SetText(posX + " " + posY + " " + posZ);
}

void Application::Render()
{
	_mainScene->Draw();

	GraphicsAPI::DisableDepthTesting();
	_hudLayer->Draw();
	GraphicsAPI::EnableDepthTesting();
}

void Application::Dispose()
{
	SafeDelete(_mainScene);
	SafeDelete(_hudLayer);
}

float horizontalAngle = 0;
float verticalAngle = 0;

void UpdateCamera(Camera& camera, const InputManager& inputManager)
{
	const float speed = 0.1f;
	const float mouseSpeed = 3.0f;

	Vector2 displacement = inputManager.GetMouseDisplacement();
	Vector3 cameraPosition = camera.GetPosition();

	horizontalAngle += mouseSpeed * displacement.x;
	verticalAngle -= mouseSpeed * displacement.y;

	if (verticalAngle > 1.57f)
		verticalAngle = 1.57f;
	if (verticalAngle < -1.57f)
		verticalAngle = -1.57f;

	Vector3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), -cos(verticalAngle) * cos(horizontalAngle));
	Vector3 right(-(float)sin(horizontalAngle - 3.14 / 2.0f), 0, (float)cos(horizontalAngle - 3.14 / 2.0f));
	Vector3 up((Vector3::GetCrossProduct(right, direction)));

	if (inputManager.KeyDown(S3_KEY_W))
		cameraPosition += speed * direction;
	if (inputManager.KeyDown(S3_KEY_S))
		cameraPosition -= speed * direction;
	if (inputManager.KeyDown(S3_KEY_A))
		cameraPosition -= speed * right;
	if (inputManager.KeyDown(S3_KEY_D))
		cameraPosition += speed * right;
	if (inputManager.KeyDown(S3_KEY_Q))
		cameraPosition -= speed * up;
	if (inputManager.KeyDown(S3_KEY_E))
		cameraPosition += speed * up;
	if (inputManager.KeyDown(S3_KEY_SPACE))
	{
		horizontalAngle = 0;
		verticalAngle = 0;
	}
	if (inputManager.KeyDown(S3_KEY_MWUP))
		camera.SetFOV(camera.GetFOV() - 1);
	if (inputManager.KeyDown(S3_KEY_MWDOWN))
		camera.SetFOV(camera.GetFOV() + 1);
	if (inputManager.KeyDown(S3_KEY_MMB))
		camera.SetFOV(45);
	if (inputManager.KeyDown(S3_KEY_0))
		cameraPosition = Vector3();

	camera.SetPosition(cameraPosition);
	camera.SetViewDirection(direction);
	camera.SetUp(up);
}

void SetLightingParameters(ShaderProgram*const shaderScene)
{
	shaderScene->Bind();

	shaderScene->SetUniform1i("material.diffuse", 0);
	shaderScene->SetUniform1i("material.specular", 1);
	shaderScene->SetUniform1f("material.shininess", 32.0f);

	shaderScene->SetUniform3f("dirLight.direction", Vector3(-1, -0.5, 1));
	shaderScene->SetUniform3f("dirLight.ambient", Vector3(0.5f, 0.5f, 0.5f));
	shaderScene->SetUniform3f("dirLight.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	shaderScene->SetUniform3f("dirLight.specular", Vector3(1.0f, 1.0f, 1.0f));

	shaderScene->SetUniform3f("pointLight.position", Vector3(2, 0.5, 0));
	shaderScene->SetUniform3f("pointLight.ambient", Vector3(0.5f, 0.5f, 0.5f));
	shaderScene->SetUniform3f("pointLight.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	shaderScene->SetUniform3f("pointLight.specular", Vector3(1.0f, 1.0f, 1.0f));
	shaderScene->SetUniform1f("pointLight.constant", 1.0f);
	shaderScene->SetUniform1f("pointLight.linear", 0.09f);
	shaderScene->SetUniform1f("pointLight.quadratic", 0.032f);

	shaderScene->SetUniform3f("spotLight.direction", Vector3(0, -0.5, 1));
	shaderScene->SetUniform3f("spotLight.ambient", Vector3(0.5f, 0.5f, 0.5f));
	shaderScene->SetUniform3f("spotLight.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	shaderScene->SetUniform3f("spotLight.specular", Vector3(1.0f, 1.0f, 1.0f));
	shaderScene->SetUniform1f("spotLight.constant", 1.0f);
	shaderScene->SetUniform1f("spotLight.linear", 0.09f);
	shaderScene->SetUniform1f("spotLight.quadratic", 0.032f);
	shaderScene->SetUniform1f("spotLight.inCutOff", (float)cos(0.226893));
	shaderScene->SetUniform1f("spotLight.outCutOff", (float)cos(0.314159));
}