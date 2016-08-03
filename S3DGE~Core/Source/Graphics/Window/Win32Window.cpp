#include <Windows.h>
#include "Window.h"

namespace S3DGE
{
	namespace Graphics
	{
		LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
		PIXELFORMATDESCRIPTOR GetPixelFormatDescriptor();
		bool SetupGLContext();

		static HWND window;
		static WNDCLASSEX windowClass = {};
		static HINSTANCE instance;
		static HDC deviceContext;
		static HGLRC renderingContext;
		static PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
		static DWORD dwExStyle;
		static DWORD dwStyle;
		static RECT windowRect;

		bool Window::InitializeWindow()
		{
			windowClass.hInstance = instance;
			windowClass.lpszClassName = "S3DGE_Win32WindowClass";
			windowClass.lpfnWndProc = WindowProcedure;
			windowClass.style = CS_DBLCLKS;
			windowClass.cbSize = sizeof(WNDCLASSEX);

			//wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			//wincl.lpszMenuName = NULL;
			//wincl.cbClsExtra = 0;
			//wincl.cbWndExtra = 0;
			windowClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

			if (!RegisterClassEx(&windowClass))
				return false;

			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //WS_EX_CLIENTEDGE;		//window extended style
			dwStyle = WS_OVERLAPPEDWINDOW;                                  //windows style
			windowRect = { 0, 0, (LONG)m_Width, (LONG)m_Height };

			if (m_FullScreen)
			{
				RECT actualDesktop;
				GetWindowRect(GetDesktopWindow(), &actualDesktop);

				DEVMODE dmScreenSettings;
				memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
				dmScreenSettings.dmSize = sizeof(dmScreenSettings);
				dmScreenSettings.dmPelsWidth =  actualDesktop.right;	 //screen width
				dmScreenSettings.dmPelsHeight = actualDesktop.bottom;	 //screen height
				dmScreenSettings.dmBitsPerPel = 32;						 //bits per pixel
				dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN == DISP_CHANGE_FAILED))
				{
					LOG_ERROR("Display mode failed");
					m_FullScreen = false;
				}
				else
				{
					dwExStyle = WS_EX_APPWINDOW;    // Window extended style.
					dwStyle = WS_POPUP;             // Windows style.
					windowRect = actualDesktop;
					//ShowCursor(FALSE);
				}
			}

			AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

			window = CreateWindowEx(
				0,
				windowClass.lpszClassName,
				m_Title,
				dwStyle,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top,
				HWND_DESKTOP,
				NULL,
				instance,
				NULL
				);

			if (!window)
			{
				LOG_ERROR("Could not create window!");
				return false;
			}

			if (!SetupGLContext())
				return false;

			Window::SetHandle(window, this);

			SetVSync(m_VSync); // VSYNC enabled by default	

			ShowWindow(window, SW_SHOW);
			SetFocus(window);

			return true;
		}

		void Window::UpdateWindow()
		{
			MSG messages;
			while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
			{
				if (messages.message == WM_QUIT)
					m_IsClosed = true;

				TranslateMessage(&messages);
				DispatchMessage(&messages);
			}

			POINT mousePosition;
			GetCursorPos(&mousePosition);
			ScreenToClient(window, &mousePosition);
			m_Mouse.x = (float)mousePosition.x;
			m_Mouse.y = (float)mousePosition.y;

			SwapBuffers(deviceContext);
		}

		void Window::SetFullScreen(bool fullscreen)
		{
			// TODO: fullscreen
		}

		void Window::SetVSync(bool vsync)
		{
			typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
			PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

			const char *extensions = (char*)glGetString(GL_EXTENSIONS);

			if (strstr(extensions, "WGL_EXT_swap_control") == 0)
				return;
			
			else
			{
				wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

				if (wglSwapIntervalEXT)
					wglSwapIntervalEXT(vsync);
			}
		}

		bool SetupGLContext()
		{
			deviceContext = GetDC(window);

			if (!deviceContext)
			{
				LOG_ERROR("Failed getting device context!");
				return false;
			}

			pixelFormatDescriptor = GetPixelFormatDescriptor();

			int pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);

			if (!pixelFormat)
			{
				LOG_ERROR("Failed choosing pixel format!");
				return false;
			}

			if (!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDescriptor))
			{
				LOG_ERROR("Failed setting pixel format!");
				return false;
			}

			renderingContext = wglCreateContext(deviceContext);

			if (!renderingContext)
			{
				LOG_ERROR("Failed to create rendering context");
				return false;
			}

			if (!wglMakeCurrent(deviceContext, renderingContext))
			{
				LOG_ERROR("Failed setting OpenGL context!");
				return false;
			}

			if (glewInit() != GLEW_OK)
			{
				LOG_ERROR("Failed to initialize GLEW!");
				return false;
			}

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			return true;
		}

		PIXELFORMATDESCRIPTOR GetPixelFormatDescriptor()
		{
			PIXELFORMATDESCRIPTOR pfd = { 0 };

			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 24;
			//result.cStencilBits = 8;
			return pfd;
		}

		LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			Window* winClassInstance = Window::GetWindowClassInstance(window);

			switch (message)
			{
			case WM_CREATE:
				break;
			case WM_DESTROY:
				wglMakeCurrent(deviceContext, NULL);	// Deselect rendering context.
				wglDeleteContext(renderingContext);		// Delete rendering context.
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				key_callback(winClassInstance, wParam, message);
				break;
			case WM_SIZE:
				resize_callback(winClassInstance, LOWORD(lParam), HIWORD(lParam));
				break;
			default:
				if (message > 512 && message < 527)
					mousebutton_callback(winClassInstance, wParam, message);
				break;
			}

			return DefWindowProc(hwnd, message, wParam, lParam);
		}

		void resize_callback(Window* window, uint width, uint height)
		{
			if (height == 0)
				height = 1;

			window->m_Width = width;
			window->m_Height = height;

			glViewport(0, 0, width, height);
			glMatrixMode(GL_PROJECTION);	//  Set current Matrix to projection
			glLoadIdentity();				//reset projection matrix
			glMatrixMode(GL_MODELVIEW);		//set modelview matrix
			glLoadIdentity();				//reset modelview matrix
		}

		void mousebutton_callback(Window* window, int key, int command)
		{
			switch (command)
			{
			case WM_LBUTTONDOWN:
				window->m_Buttons[VK_LMB] = true;
				break;
			case WM_LBUTTONUP:
				window->m_Buttons[VK_LMB] = false;
				break;
			case WM_RBUTTONDOWN:
				window->m_Buttons[VK_LMB] = false;
				break;
			case WM_RBUTTONUP:
				window->m_Buttons[VK_RMB] = false;
				break;
			case WM_MBUTTONDOWN:
				window->m_Buttons[VK_MMB] = true;
				break;
			case WM_MBUTTONUP:
				window->m_Buttons[VK_MMB] = false;
				break;
			/*case WM_MOUSEWHEEL:
			{
				short zDelta = (short)GET_WHEEL_DELTA_WPARAM(key);
				if (zDelta > 0)
					window->m_Buttons[VK_MWUP] = true;
				if (zDelta < 0)
					window->m_Buttons[VK_MWDOWN] = true;
				zDelta = 0;
				break;
			}*/
			case WM_XBUTTONDOWN:
				window->m_Buttons[VK_XBUTTON1] = true;
				break;
			case WM_XBUTTONUP:
				window->m_Buttons[VK_XBUTTON1] = false;
				break;
			}
		}

		void key_callback(Window* window, int key, int command)
		{
			switch (command)
			{
			case WM_KEYDOWN:
				window->m_Keys[key] = true;
				break;

			case WM_KEYUP:
				window->m_Keys[key] = false;
				break;

			case WM_SYSKEYDOWN:
				// Use for alt + ...
				break;
			case WM_SYSKEYUP:
				break;
			}
		}
	}
}