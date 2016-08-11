#include "Source/S3DGECommon.h"

int main()
{
	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;

	Window* window = new Window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	//window->SetVSync(false);
	ShaderProgram p("Resources/basic.vs", "Resources/basic.fs");
	int frames = 0;
	Timer t;

	while (!window->IsClosed())
	{
		window->Clear();
		glBegin(GL_QUADS);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex2d(-0.5f, -0.7f);
		glColor4f(0.0f, 1.0f, 0.0f, 0.7f);
		glVertex2d(-0.4f, 0.5f);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex2d(0.5f, 0.2f);
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
		glVertex2d(0.5f, -0.5f);
		glEnd();
		glFlush();

		if (window->KeyPressed(VK_0))
			printf("0 was pressed\n");

		if (window->MouseButtonPressed(VK_LMB))
			printf("LMB was pressed\n");

		if (window->MouseButtonPressed(VK_MWDOWN))
			printf("WMB was pressed\n");

		++frames;
		window->Update();

		if (t.ElapsedMS() > 1000.0f)
		{
			t.Start();
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	delete window;

	return 0;
}