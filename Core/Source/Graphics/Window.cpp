#include "Window.h"
#include "../Internal/Log.h"

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
				memset(&_keysDown, 0, sizeof(_keysDown));
				memset(&_keysClicked, 0, sizeof(_keysClicked));
				memset(&_buttonsDown, 0, sizeof(_buttonsDown));
				memset(&_buttonsClicked, 0, sizeof(_buttonsClicked));

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
			FontManager::Dispose();
		}

		void Window::Update()
		{
			UpdateWindow();
		}

		void Window::UpdateInputState()
		{
			memset(&_keysClicked, 0, sizeof(_keysClicked));
			memset(&_buttonsClicked, 0, sizeof(_buttonsClicked));
		}

		bool Window::KeyDown(uint key) const
		{
			return _keysDown[key];
		}

		bool Window::KeyClicked(uint key) const
		{
			return _keysClicked[key];
		}

		bool Window::KeyDoubleClicked(uint key) const
		{
			// TODO
			return false;
		}

		bool Window::MouseButtonDown(uint button) const
		{
			return _buttonsDown[button];
		}

		bool Window::MouseButtonClicked(uint button) const
		{
			return _buttonsClicked[button];
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