#include "Source/S3DGECommon.h"

int main()
{
	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;
	Window window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	//window.SetVSync(false);

	ShaderProgram p("Resources/basic.vs", "Resources/basic.fs");
	Renderer renderer(&p);

	int frames = 0;
	Timer t;

	while (!window.IsClosed())
	{
		window.Clear();
		p.Enable();
		vec2f mouse = window.GetMousePosition();
		p.SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / window.GetWidth()), (float)(9.0f - mouse.y * 9.0f / window.GetHeight())));

		renderer.Draw();
			
		++frames;

		if (window.MouseButtonPressed(VK_XBUTTON1))
			printf("LOL\n");
		if (window.MouseButtonPressed(VK_XBUTTON2))
			printf("IDK\n");
		if (window.MouseButtonPressed(VK_MWUP))
			printf("WU\n");
		if (window.MouseButtonPressed(VK_MWDOWN))
			printf("WD\n");

		window.Update();

		if (t.ElapsedMS() > 1000.0f)
		{
			t.Start();
			printf("%d fps\n", frames);
			frames = 0;
			
		}
	}

	return 0;
}