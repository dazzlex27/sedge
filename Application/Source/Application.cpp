#include "Application.h"

using namespace s3dge;
using namespace math;
using namespace graphics;
using namespace audio;

void Application::Initialize()
{
	_window = CreateGameWindow("S3DGE Application", 1280, 720, false, false);

	_shaderScene = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	_shaderHUD = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	
	//_shaderScene->SetProjection(Matrix4::GetPerspective(90.0f, 1.66f, -1.0f, 10.0f));
	_shaderScene->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 10.0f));
	_shaderHUD->SetProjection(Matrix4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 10.0f));
	
	TextureManager::Add("Box", "Resources\\box.jpg");
	TextureManager::Add("Gradient", "Resources\\gradient.bmp");
	TextureManager::Add("Brick", "Resources\\brick.jpg");
	FontManager::Add("test_font", "Resources\\SourceSansPro-Light.ttf", 32);
	SoundManager::Add("back-in-black", "Resources\\back-in-black.ogg");
	
	Sprite* rect = SpriteFactory::CreateSprite(Point2D(0, 0), Size2D(1, 1), TextureManager::Get("Box"));
	GraphicsManager::AddSprite("rect", rect);

	Label* label = LabelFactory::CreateLabel("startup...", FontManager::Get("test_font"), Point2D(0.4f, 8.2f), Size2D(2, 2));
	GraphicsManager::AddLabel("fps", label);

	float vertices[] =
	{
		0.0f, 0.0f, 0.0f,
		2.0f, 2.0f, 0.0f,
		0.0f, 2.0f, 0.0f
	};
	VertexBuffer* vbo = new VertexBuffer(vertices, sizeof(VertexData), 3);

	uint indices[] = {0, 1, 2};
	IndexBuffer* ibo = new IndexBuffer(indices, 3);

	Mesh* mesh = MeshFactory::CreateMesh(vbo, ibo, Color(0xffffffff));
	GraphicsManager::AddMesh("mesh1", mesh);

	_sceneLayer = new Layer(_shaderScene);
	_hudLayer = new Layer(_shaderHUD);

	_sceneLayer->Add(GraphicsManager::GetSprite("rect"));
	_sceneLayer->AddMesh(GraphicsManager::GetMesh("mesh1"));
	_hudLayer->Add(GraphicsManager::GetLabel("fps"));

	SoundManager::Get("back-in-black")->Play();
}

void Application::UpdateInput()
{
	float speed = 0.1f;

	_shaderHUD->Enable();
	//vec2f mouse = _window->GetMousePosition();
	//_shaderProgram->SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / _window->GetWidth()), 
	//	(float)(9.0f - mouse.y * 9.0f / _window->GetHeight())));

	GraphicsManager::GetLabel("fps")->text = std::to_string(GetFPS()) + " fps";

	if (_window->KeyDown(S3_KEY_LEFT))
		GraphicsManager::GetSprite("rect")->position.x -= speed;
	if (_window->KeyDown(S3_KEY_RIGHT))
		GraphicsManager::GetSprite("rect")->position.x += speed;
	if (_window->KeyDown(S3_KEY_UP))
		GraphicsManager::GetSprite("rect")->position.y += speed;
	if (_window->KeyDown(S3_KEY_DOWN))
		GraphicsManager::GetSprite("rect")->position.y -= speed;
	if (_window->KeyDown(S3_KEY_Q))
		GraphicsManager::GetSprite("rect")->position.z -= speed;
	if (_window->KeyDown(S3_KEY_E))
		GraphicsManager::GetSprite("rect")->position.z += speed;
	
	//if (_window->KeyClicked(S3_KEY_P))
	//{
	//	if (SoundManager::Get("back-in-black")->IsPlaying())
	//		SoundManager::Get("back-in-black")->Pause();
	//	else
	//		SoundManager::Get("back-in-black")->Play();
	//}
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
}

void LoadManySprites(Layer* layer)
{
	/*for (float y = 0; y <= 9.0f; y += 0.5f)
	{
		for (float x = 0; x <= 16.0f; x += 0.5f)
		{
			if (rand() % 4 == 0)
			{
				int a = 255;
				int r = (int)(rand() % 1000 / 1000.0f * 255);
				int g = (int)(rand() % 1000 / 1000.0f * 255);
				int b = (int)(rand() % 1000 / 1000.0f * 255);

				uint color = a << 24 | b << 16 | g << 8 | r;

				layer->Add(new Sprite(Point2D(x, y), Size2D(0.4f, 0.4f), color));
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					layer->Add(new Sprite(Point2D(x, y), Size2D(0.4f, 0.4f), TextureManager::Get("Gradient")));
					break;
				case 1:
					layer->Add(new Sprite(Point2D(x, y), Size2D(0.4f, 0.4f), TextureManager::Get("Box")));
					break;
				default:
					layer->Add(new Sprite(Point2D(x, y), Size2D(0.4f, 0.4f), TextureManager::Get("Brick")));
					break;
				}
			}
		}
	}*/
}