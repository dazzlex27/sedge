#include "Source/S3DGECommon.h"

#include "Utilities/Log.h"
#include "Utilities/Timer.h"

int main()
{
	using namespace S3DGE;
	Graphics::Window* window = new S3DGE::Graphics::Window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	window->SetVSync(false);

	int frames = 0;
	Timer t;
	while (!window->IsClosed())
	{
		window->Clear();

		glBegin(GL_QUADS);
		glVertex2d(-0.5f, -0.7f);
		glVertex2d(-0.4f, 0.5f);
		glVertex2d(0.5f, 0.2f);
		glVertex2d(0.5f, -0.5f);
		glEnd();

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