
#include "Source/S3DGECommon.h"
#include "Maths\mat4.h"

int main()
{
	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;

	Window* window = new Window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	//window->SetVSync(false);

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
			std::cout << "0 pressed" << std::endl;

		if (window->MouseButtonPressed(VK_LMB))
			std::cout << "LMB pressed" << std::endl;

		if (window->MouseButtonPressed(VK_MWDOWN))
			std::cout << "WDMB pressed" << std::endl;

		window->Update();

		if (t.ElapsedMS() > 1000.0f)
		{
			t.Start();
			std::cout << frames << " fps" << std::endl;
			frames = 0;
		}
		++frames;
	}

	delete window;

	return 0;
}