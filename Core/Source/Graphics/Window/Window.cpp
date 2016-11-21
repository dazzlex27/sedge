#include "Window.h"
#include "../../Internal/Log.h"

namespace s3dge
{
	namespace Graphics
	{
		std::map<void*, Window*> Window::_windowInstances;

		Window::Window(cstring title, uint width, uint height, bool fullscreen, bool vsync)
			: _title(title), _width(width), _height(height), _fullScreen(fullscreen), _vSync(vsync), _isClosed(false)
		{
			if (!InitializeWindow())
				LOG_FATAL("Could not initialize window!");
			else
			{
				for (int i = 0; i < MAX_KEYS; ++i)
					_keys[i] = false;

				for (int i = 0; i < MAX_BUTTONS; ++i)
					_buttons[i] = false;

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				//glEnable(GL_CULL_FACE);

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
			return _keys[key];
		}

		bool Window::KeyClicked(uint key) const
		{
			return false;
		}

		bool Window::MouseButtonPressed(uint button) const
		{
			return _buttons[button];
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
			_windowInstances[instance] = window;
		}

		Window* Window::GetWindowClassInstance(void* windowInstance)
		{
			return _windowInstances[windowInstance];
		}
	}
}