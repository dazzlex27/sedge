#include "Application.h"
#include <cmath>

using namespace s3dge;
using namespace graphics;
using namespace audio;

void Application::Initialize()
{
	CreateGameWindow("S3DGE Application", 1280, 720, false, true);

	Point2D mousePos = WindowInstance->GetMousePosition();

	_lastX = mousePos.x;
	_lastY = mousePos.y;

	horizontalAngle = 3.14;
	verticalAngle = 0;

	_shaderScene = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	_shaderHUD = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	
	_camera = new Camera();

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderHUD->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 10.0f));
	
	TextureManager::Add("Box", "Resources\\box.jpg");
	TextureManager::Add("Gradient", "Resources\\gradient.bmpzIndex");
	TextureManager::Add("Brick", "Resources\\brick.jpg");
	FontManager::Add("test_font", "Resources\\SourceSansPro-Light.ttf", 24);
	SoundManager::Add("back-in-black", "Resources\\back-in-black.ogg");
	
	Sprite* rect = SpriteFactory::CreateSprite(Point2D(0, 0), -1, Size2D(1, 1), TextureManager::Get("Box"));
	GraphicsManager::AddSprite("rect", rect);

	Label* label = LabelFactory::CreateLabel("startup...", FontManager::Get("test_font"), Point2D(0.4f, 8.2f), Size2D(2, 2));
	GraphicsManager::AddLabel("fps", label);
	Label* label2 = LabelFactory::CreateLabel("p:", FontManager::Get("test_font"), Point2D(0.4f, 7.2f), Size2D(2, 2));
	GraphicsManager::AddLabel("position", label2);

	VertexData* vertexData = new VertexData[4];

	vertexData[0].Position = Point3D(-1, 0, -2);
	vertexData[0].Color = Color(0xff00ffff);
	vertexData[1].Position = Point3D(1, 0, -2);
	vertexData[1].Color = Color(0xffff00ff);
	vertexData[2].Position = Point3D(0, 1, -2);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[3].Position = Point3D(1, 1, -2);
	vertexData[3].Color = Color(0xf0fffff0);

	VertexBuffer* vbo = new VertexBuffer(vertexData, sizeof(VertexData), 4);

	uint indices[] = {0, 1, 2, 1, 2, 3};
	IndexBuffer* ibo = new IndexBuffer(indices, 6);

	Mesh* mesh = MeshFactory::CreateMesh(vbo, ibo);

	delete[] vertexData;

	GraphicsManager::AddMesh("mesh1", mesh);

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
	float speed = 0.1f;

	Point3D cameraPosition = _camera->GetPosition();
	Vector3 position(cameraPosition);

	GraphicsManager::GetLabel("fps")->text = std::to_string(GetFPS()) + " fps";
	GraphicsManager::GetLabel("position")->text = std::to_string(cameraPosition.x) + " " + std::to_string(cameraPosition.y) + " " + std::to_string(cameraPosition.z);

	Point2D mousePos = WindowInstance->GetMousePosition();

	horizontalAngle +=  speed * (_lastX - mousePos.x);
	verticalAngle +=  speed * (_lastY - mousePos.y);

	printf("xy = %f\t%f\n", _lastX - mousePos.x, _lastY - mousePos.y);
	
	_lastX = mousePos.x;
	_lastY = mousePos.y;

	printf("angle = %f\t%f\n", horizontalAngle, verticalAngle);

	Vector3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	Vector3 right((float)sin(horizontalAngle - 3.14 / 2.0f), 0, (float)cos(horizontalAngle - 3.14 / 2.0f));
	Vector3 up((Vector3::GetCrossProduct(right, direction)));

	if (WindowInstance->KeyDown(S3_KEY_W))
		position += direction * speed;
	if (WindowInstance->KeyDown(S3_KEY_S))
		position -= direction * speed;
	if (WindowInstance->KeyDown(S3_KEY_A))
		position -= speed * right;
	if (WindowInstance->KeyDown(S3_KEY_D))
		position += speed * right;
	if (WindowInstance->KeyDown(S3_KEY_Q))
		position -= speed * up;
	if (WindowInstance->KeyDown(S3_KEY_E))
		position += speed * up;

	_camera->SetPosition(Point3D(position.x, position.y, position.z));
	_camera->SetViewDirection(direction);
	_camera->SetUp(up);

	_shaderScene->SetProjection(_camera->GetProjection());
	_shaderScene->SetView(_camera->GetView());
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
