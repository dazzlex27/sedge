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

			ShowWindow(window, SW_SHOW);
			SetFocus(window);

			return true;
		}

		void Window::UpdateWindow()
		{
			MSG messages;
			while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE) > 0)
			{
				if (messages.message == WM_QUIT)
					m_IsClosed = true;
				
				TranslateMessage(&messages);
				DispatchMessage(&messages);
			}

			SwapBuffers(deviceContext);
		}

		LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
				case WM_CREATE:
				{
					CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)pcs->lpCreateParams);
					
					break;
				}
				case WM_DESTROY:
				{
					wglMakeCurrent(deviceContext, NULL);	// Deselect rendering context.
					wglDeleteContext(renderingContext);		// Delete rendering context.
					PostQuitMessage(0);
					break;
				}
				case WM_SIZE:
				{
					unsigned int height = HIWORD(lParam);
					unsigned int width = LOWORD(lParam);

					if (height == 0)
						height = 1;

					glViewport(0, 0, width, height);

					///*      Set current Matrix to projection*/
					//glMatrixMode(GL_PROJECTION);
					//glLoadIdentity(); //reset projection matrix

					//glMatrixMode(GL_MODELVIEW); //set modelview matrix
					//glLoadIdentity(); //reset modelview matrix
					break;
				}
			}

			return DefWindowProc(hwnd, message, wParam, lParam);
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
	}
}