#include "Application.h"
#include <cmath>
#include "Logic.h"

using namespace s3dge;

void Application::Initialize()
{
	CreateGameWindow("S3DGE Application", 1280, 720, false, false);

	horizontalAngle = 0;
	verticalAngle = 0;

	_shaderScene = new ShaderProgram("Resources/Shaders/basic.vert", "Resources/Shaders/light.frag");
	_shaderHUD = new ShaderProgram("Resources/Shaders/basic.vert", "Resources/Shaders/static.frag");
	
	_camera = new FPSCamera();
	_camera->SetPosition(Vector3(0, 1.5, 4));

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderHUD->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	
	TextureManager::Add("floor", "Resources/Textures/floor.jpg");
	TextureManager::Add("box", "Resources/Textures/box.jpg");
	TextureManager::Add("brick", "Resources/Textures/brick.jpg");
	TextureManager::Add("concrete", "Resources/Textures/concrete.jpg");
	TextureManager::Add("lm-test", "Resources/Textures/lm-test.png");
	TextureManager::Add("green", "Resources/Textures/green.png");
	TextureManager::Add("blue", "Resources/Textures/blue.png");
	FontManager::Add("font1", "Resources/Fonts/Assistant-Regular.ttf", 24);
	SoundManager::Add("back-in-black", "Resources/Audio/back-in-black.ogg");
	
	Label* label = LabelFactory::CreateLabel("startup...", FontManager::Get("font1"), Point2D(0.3f, 8.4f), 0, Size2D(2, 2));
	Label* label2 = LabelFactory::CreateLabel("p:", FontManager::Get("font1"), Point2D(0.3f, 7.4f), 0, Size2D(2, 2));
	
	GraphicsManager::AddSprite("rect", SpriteFactory::CreateSprite(Point2D(0, 0), -3, Size2D(1, 1), TextureManager::Get("box")));
	GraphicsManager::AddMesh("arrow", CreateArrowMesh());
	GraphicsManager::AddMesh("room", CreateRoomMesh(TextureManager::Get("floor"), 1));
	GraphicsManager::AddMesh("cube", CreateTexturedCubeUnitSize(TextureManager::Get("concrete"), 2));
	GraphicsManager::AddMesh("cube2", CreateTexturedCubeUnitSize(TextureManager::Get("brick"), 3));
	GraphicsManager::AddMesh("cube3", CreateTexturedCubeUnitSize(TextureManager::Get("lm-test"), 4));
	GraphicsManager::AddMesh("cube4", CreateTexturedCubeUnitSize(TextureManager::Get("green"), 5));
	GraphicsManager::AddMesh("cube5", CreateTexturedCubeUnitSize(TextureManager::Get("blue"), 6));
	GraphicsManager::AddLabel("fps", label);
	GraphicsManager::AddLabel("position", label2);

	_hudLayer = new Layer(_shaderHUD);

	_hudLayer->Add(GraphicsManager::GetLabel("fps"));
	_hudLayer->Add(GraphicsManager::GetLabel("position"));

	//SoundManager::Get("back-in-black")->Play();
}

void Application::Update()
{
	Point3D cameraPosition = _camera->GetPosition();

	GraphicsManager::GetLabel("fps")->SetText(std::to_string(GetFPS()) + " fps");
	GraphicsManager::GetLabel("position")->SetText(std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z));

	UpdateCamera(InputManager::GetMouseDisplacement());

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderScene->SetView(_camera->GetView());

	_shaderScene->SetUniform3f("light.position", Vector3(0,3,-3));
	
}

void Application::UpdateCamera(const Vector2& displacement)
{
	const float speed = 0.1f;
	const float mouseSpeed = 3.0f;

	Point3D cameraPosition = _camera->GetPosition();
	Vector3 position(cameraPosition);

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
		position += speed * direction;
	if (InputManager::KeyDown(S3_KEY_S))
		position -= speed * direction;
	if (InputManager::KeyDown(S3_KEY_A))
		position -= speed * right;
	if (InputManager::KeyDown(S3_KEY_D))
		position += speed * right;
	if (InputManager::KeyDown(S3_KEY_Q))
		position -= speed * up;
	if (InputManager::KeyDown(S3_KEY_E))
		position += speed * up;
	if (InputManager::KeyDown(S3_KEY_SPACE))
	{
		horizontalAngle = 0;
		verticalAngle = 0;
	}
	if (InputManager::KeyDown(S3_KEY_MWDOWN))
		_camera->SetFOV(_camera->GetFOV() - 1);
	if (InputManager::KeyDown(S3_KEY_MWUP))
		_camera->SetFOV(_camera->GetFOV() + 1);
	if (InputManager::KeyDown(S3_KEY_MMB))
		_camera->SetFOV(45);

	_camera->SetPosition(Point3D(position.x, position.y, position.z));
	_camera->SetViewDirection(direction);
	_camera->SetUp(up);

	_shaderScene->SetProjection(_camera->GetProjection());

	_shaderScene->SetUniform3f("viewPos", Vector3(cameraPosition.x, cameraPosition.y, cameraPosition.z));
}

void Application::Render()
{
	_shaderScene->Bind();
	_shaderScene->SetModel(Matrix4::GetIdentity());
	_shaderScene->SetUniform3f("light.ambient", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("light.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("light.specular", Vector3(1.0f, 1.0f, 1.0f));
	_shaderScene->SetUniform3f("material.ambient", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("material.diffuse", Vector3(0.5f, 0.5f, 0.5f));
	_shaderScene->SetUniform3f("material.specular", Vector3(0.8f, 0.8f, 0.8f));
	_shaderScene->SetUniform1f("material.shininess", 32.0f);
	TextureManager::Get("floor")->AssignToPosition(0);
	GraphicsManager::GetMesh("room")->Draw();
	GraphicsManager::GetMesh("arrow")->Draw();
	_shaderScene->SetModel(Matrix4::Translate(Vector3(-1.5, 0, -2.5)) * Matrix4::Scale(Vector3(1.5, 1.5, 1)));
	TextureManager::Get("concrete")->AssignToPosition(1);
	GraphicsManager::GetMesh("cube")->Draw();
	_shaderScene->SetModel(Matrix4::Rotate(Vector3(0, 1, 0), 45) * Matrix4::Translate(Vector3(2, 0, 0)));
	TextureManager::Get("brick")->AssignToPosition(2);
	GraphicsManager::GetMesh("cube2")->Draw();
	_shaderScene->SetModel(Matrix4::Translate(Vector3(-0.5, 0, -1)));
	TextureManager::Get("lm-test")->AssignToPosition(3);
	GraphicsManager::GetMesh("cube3")->Draw();
	_shaderScene->SetModel(Matrix4::Translate(Vector3(-1.5, 0, -0.2)) * Matrix4::Scale(Vector3(0.5, 0.5, 0.5)));
	TextureManager::Get("green")->AssignToPosition(4);
	GraphicsManager::GetMesh("cube4")->Draw();
	_shaderScene->SetModel(Matrix4::Rotate(Vector3(0, 1, 0), 30) * Matrix4::Translate(Vector3(1, 0, 0.5)) * Matrix4::Scale(Vector3(0.8, 1, 0.5)));
	TextureManager::Get("blue")->AssignToPosition(5);
	GraphicsManager::GetMesh("cube5")->Draw();

	_hudLayer->Render();
}

void Application::Dispose()
{
	//SoundManager::Get("back-in-black")->Stop();
	SafeDelete(_hudLayer);
	SafeDelete(_shaderHUD);
	SafeDelete(_camera);
}