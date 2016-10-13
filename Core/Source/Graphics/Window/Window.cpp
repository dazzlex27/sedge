#include "Window.h"
#include "../../Internal/Log.h"

namespace s3dge
{
	namespace Graphics
	{
		std::map<void*, Window*> Window::m_WindowInstances;

		Window::Window(cstring title, uint width, uint height, bool fullscreen, bool vsync)
			: m_Title(title), m_Width(width), m_Height(height), m_FullScreen(fullscreen), m_VSync(vsync),m_IsClosed(false)
		{
			if (!InitializeWindow())
				LOG_FATAL("Could not initialize window!");
			else
			{
				for (int i = 0; i < MAX_KEYS; ++i)
					m_Keys[i] = false;

				for (int i = 0; i < MAX_BUTTONS; ++i)
					m_Buttons[i] = false;

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_DEPTH_TEST);
				//glEnable(GL_CULL_FACE);
				//glDepthFunc(GL_LESS);

				LOG_INFO("OpenGL v. ", (char*)glGetString(GL_VERSION));
				LOG_INFO("Renderer: ", (char*)glGetString(GL_RENDERER));
			}
		}

		Window::~Window()
		{
			TextureManager::Dispose();
		}

		void Window::Update()
		{
			UpdateWindow();
		}

		void Window::UpdateInput()
		{

		}

		bool Window::KeyPressed(uint key) const
		{
			return m_Keys[key];
		}

		bool Window::KeyClicked(uint key) const
		{
			return false;
		}

		bool Window::MouseButtonPressed(uint button) const
		{
			return m_Buttons[button];
		}

		bool Window::MouseButtonClicked(uint button) const
		{
			return false;
		}

		void Window::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::SetHandle(void* instance, Window* window)
		{
			m_WindowInstances[instance] = window;
		}

		Window* Window::GetWindowClassInstance(void* windowInstance)
		{
			return m_WindowInstances[windowInstance];
		}
	}
}