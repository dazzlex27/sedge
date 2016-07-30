#include "Window.h"
#include "Utilities/Log.h"

namespace S3DGE
{
	namespace Graphics
	{
		Window::Window(const char* title, uint width, uint height, bool fullscreen, bool vsync)
			: m_Title(title), m_Width(width), m_Height(height), m_FullScreen(fullscreen), m_VSync(vsync)
		{
			if (!InitializeWindow())
			{
				LOG_FATAL("Could not initialize window!");
			}
			else
			{
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				
				LOG_INFO((char*)glGetString(GL_VERSION));
			}
		}

		Window::~Window()
		{
		}

		void Window::Update()
		{
			UpdateWindow();
		}

		void Window::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}