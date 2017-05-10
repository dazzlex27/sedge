#include "Application.h"
#include <cmath>

using namespace s3dge;
using namespace graphics;
using namespace audio;

Mesh* CreateArrowPolygon();

void Application::Initialize()
{
	CreateGameWindow("S3DGE Application", 1280, 720, false, true);

	Point2D mousePos = WindowInstance->GetMousePosition();

	horizontalAngle = -1;
	verticalAngle = -1;

	_shaderScene = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	_shaderHUD = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	
	_camera = new FPSCamera();

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderHUD->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 10.0f));
	
	TextureManager::Add("Box", "Resources\\box.jpg");
	TextureManager::Add("Gradient", "Resources\\gradient.bmpzIndex");
	TextureManager::Add("Brick", "Resources\\brick.jpg");
	FontManager::Add("test_font", "Resources\\SourceSansPro-Light.ttf", 24);
	SoundManager::Add("back-in-black", "Resources\\back-in-black.ogg");
	
	Sprite* rect = SpriteFactory::CreateSprite(Point2D(0, 0), -3, Size2D(1, 1), TextureManager::Get("Box"));
	GraphicsManager::AddSprite("rect", rect);

	Label* label = LabelFactory::CreateLabel("startup...", FontManager::Get("test_font"), Point2D(0.4f, 8.2f), Size2D(2, 2));
	GraphicsManager::AddLabel("fps", label);
	Label* label2 = LabelFactory::CreateLabel("p:", FontManager::Get("test_font"), Point2D(0.4f, 7.2f), Size2D(2, 2));
	GraphicsManager::AddLabel("position", label2);

	GraphicsManager::AddMesh("mesh1", CreateArrowPolygon());

	_sceneLayer = new Layer(_shaderScene);
	_hudLayer = new Layer(_shaderHUD);

	_sceneLayer->Add(GraphicsManager::GetSprite("rect"));
	_sceneLayer->AddMesh(GraphicsManager::GetMesh("mesh1"));
	_hudLayer->Add(GraphicsManager::GetLabel("fps"));
	_hudLayer->Add(GraphicsManager::GetLabel("position"));

	//SoundManager::Get("back-in-black")->Play();
}

void Application::UpdateInput()
{
	Point3D cameraPosition = _camera->GetPosition();

	GraphicsManager::GetLabel("fps")->text = std::to_string(GetFPS()) + " fps";
	GraphicsManager::GetLabel("position")->text = std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z);

	UpdateCamera(WindowInstance->GetMousePosition());

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderScene->SetView(_camera->GetView());
}

void Application::UpdateCamera(const Point2D& mousePosition)
{
	if (horizontalAngle == -1)
	{
		horizontalAngle = 0;
		verticalAngle = 0;
		return;
	}

	float speed = 0.1f;
	float mouseSpeed = 0.005f;

	Point3D cameraPosition = _camera->GetPosition();
	Vector3 position(cameraPosition);

	horizontalAngle -= mouseSpeed * (WindowInstance->GetWidth() / 2 - mousePosition.x);
	verticalAngle += mouseSpeed * (WindowInstance->GetHeight() / 2 - mousePosition.y);

	//printf("angle = %f\t%f\n", horizontalAngle, verticalAngle);
	//printf("xy = %f\t%f\n", (1280 / 2 - mousePosition.x), (1280 / 2 - mousePosition.y));

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
	_camera->SetUp(up);
}

void Application::Render()
{
	_sceneLayer->Render();
	_hudLayer->Render();
}

void Application::Dispose()
{
	SoundManager::Get("back-in-black")->Stop();
	SafeDelete(_hudLayer);
	SafeDelete(_sceneLayer);
	SafeDelete(_shaderHUD);
	SafeDelete(_camera);
}

Mesh* CreateArrowPolygon()
{
	VertexData* vertexData = new VertexData[3];

	vertexData[0].Position = Point3D(1, 1, -5);
	vertexData[0].Color = Color(0xff00ffff);
	vertexData[1].Position = Point3D(2, 0.5, -5);
	vertexData[1].Color = Color(0xffff00ff);
	vertexData[2].Position = Point3D(1, 0, -5);
	vertexData[2].Color = Color(0xffffff00);

	VertexBuffer* vbo = new VertexBuffer(vertexData, sizeof(VertexData), 4);

	uint indices[] = { 0, 1, 2 };
	IndexBuffer* ibo = new IndexBuffer(indices, 3);

	Mesh* mesh = MeshFactory::CreateMesh(vbo, ibo);

	delete[] vertexData;

	return mesh;
}