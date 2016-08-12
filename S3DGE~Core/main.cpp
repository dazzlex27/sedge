#include "Source/S3DGECommon.h"

int main()
{
	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;
	Window window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	window.SetVSync(false);
	ShaderProgram p("Resources/basic.vs", "Resources/basic.fs");
	Renderer renderer(&p);
	int frames = 0;
	Timer t;

	p.Enable();

	while (!window.IsClosed())
	{
		window.Clear();
		
		renderer.Draw();
			
		++frames;

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