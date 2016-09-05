#include "Source/S3DGECommon.h"

int main()
{
	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;

	Window window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	window.SetVSync(false);

	Renderable2D sprite1(vec3f(0, 0, 0), vec2f(1, 1), vec4f(1, 1, 0, 1));

	ShaderProgram p("Resources/basic.vs", "Resources/basic.fs");
	Renderer2D renderer(&p);

	int frames = 0;
	Timer t;

	while (!window.IsClosed())
	{
		window.Clear();

		p.Enable();
		vec2f mouse = window.GetMousePosition();
		p.SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / window.GetWidth()), (float)(9.0f - mouse.y * 9.0f / window.GetHeight())));
		renderer.Submit(&sprite1);
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