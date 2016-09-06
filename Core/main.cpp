#include "Source/S3DGECommon.h"

int main()
{
	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;

	Window window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	window.SetVSync(false);

	mat4 ortho = mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	ShaderProgram p("Resources/basic.vs", "Resources/basic.fs");

	std::vector<Renderable2D*> sprites;

	srand((uint)time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05f)
	{
		for (float x = 0; x < 16.0f; x += 0.05f)
		{
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, Maths::vec4f(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	Sprite sprite(5, 5, 4, 4, Maths::vec4f(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, Maths::vec4f(0.2f, 0, 1, 1));
	Renderer2D renderer;

	int frames = 0;
	Timer t;

	while (!window.IsClosed())
	{
		window.Clear();

		p.Enable();
		vec2f mouse = window.GetMousePosition();
		p.SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / window.GetWidth()), (float)(9.0f - mouse.y * 9.0f / window.GetHeight())));
		
		renderer.Begin();
		for (uint i = 0; i < sprites.size(); i++)
		{
			renderer.Submit(sprites[i]);
		}
		renderer.Flush();
		renderer.End();

		window.Update();
		
		++frames;
		if (t.ElapsedMS() > 1000.0f)
		{
			t.Start();
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	return 0;
}