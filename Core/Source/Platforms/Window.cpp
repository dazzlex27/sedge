#include "Window.h"

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
				memset(&_buttonsDoubleClicked, 0, sizeof(_buttonsDoubleClicked));
				for (int i = 0; i < MAX_BUTTONS; ++i)
					_doubleClickTimers[i] = new Timer();

				_elapsedDoubleClickThreshold = 1.0f;
				clicks = 0;

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
			for (int i = 0; i < MAX_BUTTONS; ++i)
				SafeDelete(_doubleClickTimers[i]);
		}

		void Window::UpdateInputState()
		{
			if (_buttonsDown[VK_MWUP])
				_buttonsDown[VK_MWUP] = false;
			if (_buttonsDown[VK_MWDOWN])
				_buttonsDown[VK_MWDOWN] = false;

			memset(&_keysClicked, 0, sizeof(_keysClicked));
			memset(&_buttonsClicked, 0, sizeof(_buttonsClicked));
			for (int i = 0; i < MAX_BUTTONS; ++i)
				if (_doubleClickTimers[i]->IsRunning())
					if (_doubleClickTimers[i]->ElapsedS() > _elapsedDoubleClickThreshold)
					{
						LOG_WARNING("double click timer reset");
						_doubleClickTimers[i]->Stop();
					}

			memset(&_buttonsDoubleClicked, 0, sizeof(_buttonsDoubleClicked));
		}

		bool Window::KeyDown(uint key) const
		{
			return _keysDown[key];
		}

		bool Window::KeyClicked(uint key) const
		{
			return _keysClicked[key];
		}

		bool Window::MouseButtonDoubleClicked(uint key) const
		{
			return _buttonsDoubleClicked[key];
		}

		bool Window::MouseButtonDown(uint button) const
		{
			return _buttonsDown[button];
		}

		bool Window::MouseButtonClicked(uint button) const
		{
			return _buttonsClicked[button];
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