#include "Application.h"

using namespace std;
using namespace s3dge;

static void UpdateCamera(Camera& camera, const InputManager& inputManager);
static void SetLightingParameters(ShaderProgram*const shaderScene);

void Application::LoadAssets()
{
	_shaderManager->Add("scene", "Resources/Shaders/scene.vert", "Resources/Shaders/scene.frag");
	_shaderManager->Add("hud", "Resources/Shaders/hud.vert", "Resources/Shaders/hud.frag");
	_shaderManager->Add("skybox", "Resources/Shaders/skybox.vert", "Resources/Shaders/skybox.frag");
	_shaderManager->Add("terrain", "Resources/Shaders/terrain.vert", "Resources/Shaders/terrain.frag");

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

	_renderable3DManager->AddModel("nano", _graphicsObjFactorySet.ModelFactory.CreateModel("Resources/Models/nanosuit/nanosuit.obj"));
	_renderable3DManager->AddModel("sponza", _graphicsObjFactorySet.ModelFactory.CreateModel("Resources/Models/sponza/sponza.obj"));
	_renderable3DManager->AddSkybox("sky1", _graphicsObjFactorySet.SkyboxFactory.CreateSkybox(_textureManager->GetCubemap("skybox")));
}

Application::Application()
{
	_fontManager = new FontManager();
	_shaderManager = new ShaderManager();
	_textureManager = new TextureManager();
	_renderable2DManager = new Renderable2DManager();
	_renderable3DManager = new Renderable3DManager();
}

Application::~Application()
{
	SafeDelete(_fontManager);
	SafeDelete(_shaderManager);
	SafeDelete(_textureManager);
	SafeDelete(_renderable2DManager);
	SafeDelete(_renderable3DManager);
}

void Application::Initialize(const InitializationToolset& initToolset)
{
	_graphicsObjFactorySet = initToolset.GraphicsObjFactorySet;

	CreateGameWindow("S3DGE Application", 1280, 720, false, false);

	_inputManager = MainWindow->GetInputManager();

	LoadAssets();

	_terrain = new Terrain(_textureManager->GetTex2D("terrain"));

	_cube1 = new Cube(0xff00ff);
	_cube2 = new Cube(0x00ffff);

	_camera = new FPSCamera();
	_camera->SetPosition(Vector3(0, 1, 0));

	_shaderManager->GetShader("scene")->SetProjection(_camera->GetProjection());
	_shaderManager->GetShader("hud")->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	Label* label = _graphicsObjFactorySet.LabelFactory.CreateLabel("startup...", _fontManager->GetFont("font1"), Vector2(0.1f, 8.7f), 0, Size2D(2, 2));
	Label* label2 = _graphicsObjFactorySet.LabelFactory.CreateLabel("p:", _fontManager->GetFont("font1"), Vector2(0.1f, 8.4f), 0, Size2D(2, 2));
	
	_renderable2DManager->AddLabel("fps", label);
	_renderable2DManager->AddLabel("position", label2);

	_mainScene = new Scene(_shaderManager->GetShader("scene"));
	_mainScene->SetActiveCamera(_camera);

	_hudLayer = new Layer2D(_shaderManager->GetShader("hud"));

	_hudLayer->Add(_renderable2DManager->GetLabel("fps"));
	_hudLayer->Add(_renderable2DManager->GetLabel("position"));

	ShaderProgram* shaderScene = _shaderManager->GetShader("scene");

	SetLightingParameters(shaderScene);
}

void Application::UpdateLogic()
{
	UpdateCamera(*_camera, *_inputManager);
	const Vector3& cameraPosition = _camera->GetPosition();

	ShaderProgram*const shaderScene = _shaderManager->GetShader("scene");
	shaderScene->Bind(); 
	shaderScene->SetUniform3f("spotLight.position", cameraPosition);
	shaderScene->SetUniform3f("spotLight.direction", _camera->GetViewDirection());

	_renderable2DManager->GetLabel("fps")->SetText(std::to_string(GetFPS()) + " fps");
	_renderable2DManager->GetLabel("position")->SetText(std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z));

	_mainScene->Update();
	shaderScene->SetUniform3f("viewPos", cameraPosition);
}

void Application::Render()
{
	const Matrix4& projection = _camera->GetProjection();
	const Matrix4& view = _camera->GetView();

	DrawTerrain(projection, view);
	DrawScene(projection, view);
	DrawSkybox(projection, view);
	DrawUI();
}

void Application::Dispose()
{
	SafeDelete(_mainScene);
	SafeDelete(_hudLayer);
	SafeDelete(_camera);

	SafeDelete(_fontManager);
	SafeDelete(_shaderManager);
	SafeDelete(_textureManager);
	SafeDelete(_renderable2DManager);
	SafeDelete(_renderable3DManager);

	SafeDelete(_terrain);

	SafeDelete(_cube1);
}

void Application::DrawUI()
{
	GraphicsAPI::DisableDepthTesting();
	_shaderManager->GetShader("hud")->Bind();
	_hudLayer->Draw();
	GraphicsAPI::EnableDepthTesting();
}

void Application::DrawTerrain(const Matrix4& projectionMatrix, const Matrix4& viewMatrix)
{
	ShaderProgram* shaderTerrain = _shaderManager->GetShader("terrain");
	shaderTerrain->SetProjection(projectionMatrix);
	shaderTerrain->SetView(viewMatrix);

	_terrain->Render();
}

void Application::DrawSkybox(const Matrix4& projectionMatrix, const Matrix4& viewMatrix)
{
	ShaderProgram* shaderSkybox = _shaderManager->GetShader("skybox");
	shaderSkybox->SetProjection(projectionMatrix);
	shaderSkybox->SetView(viewMatrix);

	GraphicsAPI::DisableDepthMask();
	_renderable3DManager->GetSkybox("sky1")->Draw();
	GraphicsAPI::EnableDepthMask();
}

void Application::DrawScene(const Matrix4& projectionMatrix, const Matrix4& viewMatrix)
{
	ShaderProgram* shaderScene = _shaderManager->GetShader("scene");
	shaderScene->SetProjection(projectionMatrix);
	shaderScene->SetView(viewMatrix);

	_cube1->Draw();

	shaderScene->SetModel(Matrix4::GetScale(Vector3(0.008f, 0.008f, 0.008f)));
	_renderable3DManager->GetModel("sponza")->Draw();
	shaderScene->SetModel(Matrix4::GetTranslation(Vector3(0, 0, -1.5f)) * Matrix4::GetScale(Vector3(0.1f, 0.1f, 0.1f)));
	_renderable3DManager->GetModel("nano")->Draw();
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