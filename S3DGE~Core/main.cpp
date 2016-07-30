#include <iostream>
#include "Source/S3DGECommon.h"
#include "Utilities/Log.h"

int main()
{
	using namespace S3DGE;

	Graphics::Window* window = new S3DGE::Graphics::Window("S3DGE Test", 1280, 720, false);

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
	}

	delete window;

	return 0;
}