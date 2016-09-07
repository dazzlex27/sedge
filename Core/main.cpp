#include "Source/S3DGECommon.h"

int main()
{
	srand((uint)time(NULL));

	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;

	Window window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	window.SetVSync(false);

	Renderer2D renderer;
	mat4 ortho = mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	ShaderProgram shaderProgram("Resources/basic.vs", "Resources/basic.fs");
	shaderProgram.Enable();
	shaderProgram.SetUniformMat4fv("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;

	for (float y = 0; y < 9.0f; y += 0.5f)
		for (float x = 0; x < 16.0f; x += 0.5f)
			sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, Maths::vec4f(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));

	int frames = 0;
	Timer t;

	while (!window.IsClosed())
	{
		window.Clear();

		shaderProgram.Enable();
		vec2f mouse = window.GetMousePosition();
		shaderProgram.SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / window.GetWidth()), (float)(9.0f - mouse.y * 9.0f / window.GetHeight())));
		
		renderer.Begin();
		for (uint i = 0; i < sprites.size(); i++)
			renderer.Submit(sprites[i]);
		renderer.End();
		renderer.Flush();

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