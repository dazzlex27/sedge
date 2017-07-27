#include "Application.h"
#include <cmath>
//#include "Logic.h"

using namespace s3dge;

void Application::Initialize()
{
	CreateGameWindow("S3DGE Application", 1280, 720, false, false);
	LOG_INFO("Let's start");

	/*Point2D mousePos = WindowInstance->GetMousePosition();

	horizontalAngle = 0;
	verticalAngle = 0;

	_shaderScene = new ShaderProgram("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	_shaderHUD = new ShaderProgram("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	
	_camera = new FPSCamera();

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderHUD->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	
	TextureManager::Add("Box", "Resources/Textures/box.jpg");
	TextureManager::Add("Brick", "Resources/Textures/brick.jpg");
	FontManager::Add("test_font", "Resources/Fonts/Assistant-Regular.ttf", 24);
	SoundManager::Add("back-in-black", "Resources/Audio/back-in-black.ogg");
	
	Sprite* rect = SpriteFactory::CreateSprite(Point2D(0, 0), -3, Size2D(1, 1), TextureManager::Get("Box"));
	GraphicsManager::AddSprite("rect", rect);

	Label* label = LabelFactory::CreateLabel("startup...", FontManager::Get("test_font"), Point2D(0.3f, 8.4f), 0, Size2D(2, 2));
	GraphicsManager::AddLabel("fps", label);
	Label* label2 = LabelFactory::CreateLabel("p:", FontManager::Get("test_font"), Point2D(0.3f, 7.4f), 0, Size2D(2, 2));
	GraphicsManager::AddLabel("position", label2);

	GraphicsManager::AddMesh("arrow", CreateArrowMesh());
	GraphicsManager::AddMesh("room", CreateRoomMesh());

	_sceneLayer2D = new Layer2D(_shaderScene);
	_sceneLayer3D = new Layer(_shaderScene);
	_hudLayer = new Layer2D(_shaderHUD);

	_sceneLayer2D->Add(GraphicsManager::GetSprite("rect"));
	_sceneLayer3D->Add(GraphicsManager::GetMesh("arrow"));
	_sceneLayer3D->Add(GraphicsManager::GetMesh("room"));
	_hudLayer->Add(GraphicsManager::GetLabel("fps"));
	_hudLayer->Add(GraphicsManager::GetLabel("position"));*/

	//SoundManager::Get("back-in-black")->Play();
}

void Application::Update()
{
	/*Point3D cameraPosition = _camera->GetPosition();

	GraphicsManager::GetLabel("fps")->text = std::to_string(GetFPS()) + " fps";
	GraphicsManager::GetLabel("position")->text = std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z);

	UpdateCamera(WindowInstance->GetMousePosition());

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderScene->SetView(_camera->GetView());*/
}

void Application::UpdateCamera(const Point2D& mousePosition)
{
	/*float speed = 0.1f;
	float mouseSpeed = 0.005f;

	Point3D cameraPosition = _camera->GetPosition();
	Vector3 position(cameraPosition);

	horizontalAngle -= mouseSpeed * (WindowInstance->GetWidth() / 2 - mousePosition.x);
	verticalAngle += mouseSpeed * (WindowInstance->GetHeight() / 2 - mousePosition.y);

	if (verticalAngle > 1.57f)
		verticalAngle = 1.57f;
	if (verticalAngle < -1.57f)
		verticalAngle = -1.57f;

	Vector3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), -cos(verticalAngle) * cos(horizontalAngle));
	Vector3 right(-(float)sin(horizontalAngle - 3.14 / 2.0f), 0, (float)cos(horizontalAngle - 3.14 / 2.0f));
	Vector3 up((Vector3::GetCrossProduct(right, direction)));

	if (WindowInstance->KeyDown(S3_KEY_W))
		position += speed * direction;
	if (WindowInstance->KeyDown(S3_KEY_S))
		position -= speed * direction;
	if (WindowInstance->KeyDown(S3_KEY_A))
		position -= speed * right;
	if (WindowInstance->KeyDown(S3_KEY_D))
		position += speed * right;
	if (WindowInstance->KeyDown(S3_KEY_Q))
		position -= speed * up;
	if (WindowInstance->KeyDown(S3_KEY_E))
		position += speed * up;
	if (WindowInstance->KeyDown(S3_KEY_SPACE))
	{
		horizontalAngle = 0;
		verticalAngle = 0;
	}

	_camera->SetPosition(Point3D(position.x, position.y, position.z));
	_camera->SetViewDirection(direction);
	_camera->SetUp(up);*/

	/*if (WindowInstance->MouseButtonDown(S3_KEY_MWUP))
		LOG_INFO("MW up");
	if (WindowInstance->MouseButtonDown(S3_KEY_MWDOWN))
		LOG_INFO("MW down");*/
}

void Application::Render()
{
	/*_sceneLayer2D->Render();
	_sceneLayer3D->Render();
	_hudLayer->Render();*/
}

void Application::Dispose()
{
	/*SoundManager::Get("back-in-black")->Stop();
	SafeDelete(_hudLayer);
	SafeDelete(_sceneLayer2D);
	SafeDelete(_sceneLayer3D);
	SafeDelete(_shaderHUD);
	SafeDelete(_camera);*/
}