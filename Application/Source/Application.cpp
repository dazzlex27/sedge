#include "Application.h"

using namespace s3dge;
using namespace Maths;
using namespace Graphics;

void Application::Initialize()
{
	_window = CreateGameWindow("S3DGE Application", 1280, 720, false, false);
	_shaderProgram = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	_shaderProgram->SetProjection(mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	
	TextureManager::Add("Box", "Resources\\box.jpg");
	TextureManager::Add("Gradient", "Resources\\gradient.bmp");
	TextureManager::Add("Brick", "Resources\\brick.jpg");
	FontManager::Add("test_font", "Resources\\SourceSansPro-Light.ttf", 32);

	_layer = new Layer(_shaderProgram, new Renderer2D());

	_fps = new Label("Test", FontManager::Get("test_font"), 0.4f, 8.2f, 2, 2, 0xffffffff);

	for (float y = 0; y < 9.0f; y += 0.5f)
	{
		for (float x = 0; x < 16.0f; x += 0.5f)
		{
			if (rand() % 4 == 0)
			{
				int a = 255;
				int r = (int)(rand() % 1000 / 1000.0f * 255);
				int g = (int)(rand() % 1000 / 1000.0f * 255);
				int b = (int)(rand() % 1000 / 1000.0f * 255);

				uint color = a << 24 | b << 16 | g << 8 | r;

				_layer->Add(new Sprite(x, y, 0.4f, 0.4f, color));
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					_layer->Add(new Sprite(x, y, 0.4f, 0.4f, TextureManager::Get("Gradient")));
					break;
				case 1:
					_layer->Add(new Sprite(x, y, 0.4f, 0.4f, TextureManager::Get("Box")));
					break;
				default:
					_layer->Add(new Sprite(x, y, 0.4f, 0.4f, TextureManager::Get("Brick")));
					break;
				}
			}
		}
	}

	_layer->Add(_fps);
}

void Application::UpdateInput()
{
	_shaderProgram->Enable();
	vec2f mouse = _window->GetMousePosition();
	_shaderProgram->SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / _window->GetWidth()), 
		(float)(9.0f - mouse.y * 9.0f / _window->GetHeight())));
	std::string text = std::to_string(GetFPS()) + " fps";
	_fps->text = text.c_str();
}

void Application::Render()
{
	_layer->Render();
}

void Application::Dispose()
{
	SafeDelete(_layer);
	SafeDelete(_shaderProgram);
}