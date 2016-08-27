#include <Windows.h>
#include "Window.h"

namespace S3DGE
{
	namespace Graphics
	{
		LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
		PIXELFORMATDESCRIPTOR GetPixelFormatDescriptor();
		bool SetupGLContext();

		HWND window;
		HINSTANCE instance;
		HDC deviceContext;
		WNDCLASSEX windowClass = {};
		HGLRC renderingContext;
		PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
		WINDOWPLACEMENT wpc;

		LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			Window* winInstance = Window::GetWindowClassInstance(window);

			switch (message)
			{
			case WM_CREATE:
				break;
			case WM_DESTROY:
				wglMakeCurrent(deviceContext, NULL);	// Deselect rendering context.
				wglDeleteContext(renderingContext);
				PostQuitMessage(0);
				break;
			case WM_MENUCHAR:
				if (LOWORD(wParam) == VK_RETURN && winInstance)
					return MAKELRESULT(0, MNC_CLOSE);
				return MAKELRESULT(0, MNC_IGNORE);
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				if (winInstance)
					key_callback(winInstance, wParam, message);
				break;
			case WM_SIZE:
				if (winInstance)
					resize_callback(winInstance, LOWORD(lParam), HIWORD(lParam));
				break;
			default:
				if (message > 512 && message < 527 && winInstance)
					mousebutton_callback(winInstance, wParam, message);
			}

			return DefWindowProc(hwnd, message, wParam, lParam);
		}

		bool Window::InitializeWindow()
		{
			windowClass.hInstance = instance;
			windowClass.lpszClassName = "S3DGE_Win32WindowClass";
			windowClass.lpfnWndProc = WindowProcedure;
			windowClass.style = CS_DBLCLKS;
			windowClass.cbSize = sizeof(WNDCLASSEX);
			windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			windowClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

			if (!RegisterClassEx(&windowClass))
				return false;

			window = CreateWindowEx(
				WS_EX_CLIENTEDGE,
				windowClass.lpszClassName,
				m_Title,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				m_Width,
				m_Height,
				HWND_DESKTOP,
				NULL,
				instance,
				NULL
				);

			if (!window)
			{
				LOG_FATAL("Could not create window!");
				return false;
			}

			if (!SetupGLContext())
				return false;

			Window::SetHandle(window, this);

			SetFullScreen(m_FullScreen);
			SetVSync(m_VSync);

			ShowWindow(window, SW_SHOW);
			SetFocus(window);

			return true;
		}

		void Window::UpdateWindow()
		{
			if (m_Buttons[VK_MWUP])
				m_Buttons[VK_MWUP] = false;
			if (m_Buttons[VK_MWDOWN])
				m_Buttons[VK_MWDOWN] = false;

			POINT mousePosition;
			GetCursorPos(&mousePosition);
			ScreenToClient(window, &mousePosition);
			m_Mouse.x = (float)mousePosition.x;
			m_Mouse.y = (float)mousePosition.y;

			MSG messages;
			while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
			{
				if (messages.message == WM_QUIT)
					m_IsClosed = true;

				TranslateMessage(&messages);
				DispatchMessage(&messages);				
			}

			SwapBuffers(deviceContext);
		}

		void Window::SetFullScreen(bool fullscreen)
		{
			if (fullscreen)
			{
				GetWindowPlacement(window, &wpc);
				SetWindowLongPtr(window, GWL_STYLE, WS_POPUP);
				SetWindowLong(window, GWL_EXSTYLE, WS_EX_TOPMOST);
				ShowWindow(window, SW_SHOWMAXIMIZED);
			}
			else
			{
				SetWindowLongPtr(window, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
				SetWindowLong(window, GWL_EXSTYLE, WS_EX_CLIENTEDGE);
				SetWindowPlacement(window, &wpc);
				ShowWindow(window, SW_SHOWDEFAULT);
			}

			m_FullScreen = fullscreen;
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
			case WM_XBUTTONDOWN:
				if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
					window->m_Buttons[VK_XBUTTON1] = true;
				else
					window->m_Buttons[VK_XBUTTON2] = true;
				break;
			case WM_XBUTTONUP:
				if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
					window->m_Buttons[VK_XBUTTON1] = false;
				else
					window->m_Buttons[VK_XBUTTON2] = false;
				break;
			case WM_MOUSEWHEEL:
				short zDelta = (short)GET_WHEEL_DELTA_WPARAM(key);
				if (zDelta > 0)
					window->m_Buttons[VK_MWUP] = true;
				if (zDelta < 0)
					window->m_Buttons[VK_MWDOWN] = true;
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
				if (key == VK_RETURN)
					window->SetFullScreen(!window->IsFullScreen());
				break;
			}
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
			pfd.cStencilBits = 8;
			return pfd;
		}
	}
}