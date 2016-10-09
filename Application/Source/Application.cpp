#include <S3DGE.h>
#include <string>

using namespace s3dge;
using namespace Graphics;
using namespace Maths;

class Application : public S3DGE
{
private:
	Window* _window;
	Label* _fps;
	ShaderProgram* _shaderProgram;
	Renderer2D* _renderer;
	std::vector<Renderable2D*> _sprites;

public:
	Application()
	{

	}

	~Application()
	{
		delete _fps;
		delete _shaderProgram;
	}

	void Initialize() override
	{
		_window = CreateGameWindow("S3DGE Application", 1280, 720, false, false);
		_shaderProgram = new ShaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
		mat4 ortho = mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		int textureIDs[] =
		{
			0,1,2,3,4,5,6,7,8,9
		};

		_shaderProgram->Enable();
		_shaderProgram->SetUniform1iv("textureArray", 10, textureIDs);
		_shaderProgram->SetUniformMat4fv("pr_matrix", ortho);

		TextureManager::AddTexture(new Texture("Box", "Resources\\box.jpg"));
		TextureManager::AddTexture(new Texture("Gradient", "Resources\\gradient.bmp"));
		TextureManager::AddTexture(new Texture("Brick", "Resources\\brick.jpg"));

		_fps = new Label("Test", 0.4f, 8.2f, 2, 2, 0xffffffff);

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

					_sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, color));
				}
				else
				{
					switch (rand() % 3)
					{
					case 0:
						_sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, TextureManager::GetTexture("Gradient")));
					case 1:
						_sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, TextureManager::GetTexture("Box")));
					default:
						_sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, TextureManager::GetTexture("Brick")));
					}
				}
			}
		}

		_renderer = new Renderer2D();
	}

	void UpdateInput() override
	{

	}

	void Render() override
	{
		_shaderProgram->Enable();
		vec2f mouse = _window->GetMousePosition();
		_shaderProgram->SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / _window->GetWidth()), (float)(9.0f - mouse.y * 9.0f / _window->GetHeight())));
		std::string text = std::to_string(GetFPS()) + " fps";
		_fps->text = text.c_str();

		_renderer->Begin();
		_renderer->SubmitLabel(_fps);
		for (uint i = 0; i < _sprites.size(); i++)
			_renderer->SubmitRenderable(_sprites[i]);
		_renderer->End();
		_renderer->Flush();
	}

	void Dispose() override
	{

	}
};

int main()
{
	Application app;
	app.StartUp();

	return 0;
}