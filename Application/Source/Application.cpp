#include "Application.h"

using namespace s3dge;
using namespace maths;
using namespace graphics;
using namespace audio;

void Application::Initialize()
{
	_window = CreateGameWindow("S3DGE Application", 1280, 720, false, false);
	_shaderProgram = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	_shaderProgram->SetProjection(mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	
	TextureManager::Add("Box", "Resources\\box.jpg");
	TextureManager::Add("Gradient", "Resources\\gradient.bmp");
	TextureManager::Add("Brick", "Resources\\brick.jpg");
	FontManager::Add("test_font", "Resources\\SourceSansPro-Light.ttf", 32);
	SoundManager::Add("back-in-black", "Resources\\back-in-black.ogg");
	GraphicsManager::AddSprite("rect", 4, 3, 3, 3, 0xffffffff, TextureManager::Get("Brick"));
	GraphicsManager::AddLabel("fps", "startup...", FontManager::Get("test_font"), 0.4f, 8.2f, 2, 2);

	_layer = new Layer(_shaderProgram, _window);

	_layer->Add(GraphicsManager::GetSprite("rect"));
	_layer->Add(GraphicsManager::GetLabel("fps"));

	SoundManager::Get("back-in-black")->Play();
}

void Application::UpdateInput()
{
	float speed = 0.1f;

	_shaderProgram->Enable();
	vec2f mouse = _window->GetMousePosition();
	_shaderProgram->SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / _window->GetWidth()), 
		(float)(9.0f - mouse.y * 9.0f / _window->GetHeight())));

	GraphicsManager::GetLabel("fps")->text = std::to_string(GetFPS()) + " fps";

	if (_window->KeyDown(VK_LEFT))
		GraphicsManager::GetSprite("rect")->position.x -= speed;
	if (_window->KeyDown(VK_RIGHT))
		GraphicsManager::GetSprite("rect")->position.x += speed;
	if (_window->KeyDown(VK_UP))
		GraphicsManager::GetSprite("rect")->position.y += speed;
	if (_window->KeyDown(VK_DOWN))
		GraphicsManager::GetSprite("rect")->position.y -= speed;

	if (_window->KeyClicked(VK_P))
	{
		if (SoundManager::Get("back-in-black")->IsPlaying())
			SoundManager::Get("back-in-black")->Pause();
		else
			SoundManager::Get("back-in-black")->Play();
	}
}

void Application::Render()
{
	_layer->Render();
}

void Application::Dispose()
{
	SoundManager::Get("back-in-black")->Stop();
	SafeDelete(_layer);
	SafeDelete(_shaderProgram);
}

void LoadManySprites(Layer* layer)
{
	for (float y = 0; y <= 9.0f; y += 0.5f)
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

				layer->Add(new Sprite(x, y, 0.4f, 0.4f, color));
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					layer->Add(new Sprite(x, y, 0.4f, 0.4f, TextureManager::Get("Gradient")));
					break;
				case 1:
					layer->Add(new Sprite(x, y, 0.4f, 0.4f, TextureManager::Get("Box")));
					break;
				default:
					layer->Add(new Sprite(x, y, 0.4f, 0.4f, TextureManager::Get("Brick")));
					break;
				}
			}
		}
	}
}