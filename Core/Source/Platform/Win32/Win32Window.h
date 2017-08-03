/*
===========================================================================
Win32Window.h

Main Win32 implementation file.
===========================================================================
*/

#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include "System/Log.h"
#include "Platform/Window.h"
#include "Win32InputKeys.h"
#include "System/Timer.h"
#include "System/InputManager.h"

namespace s3dge
{
#ifdef S3_DEBUG
#include "Win32OpenGLDebug.h"
#endif

	static HCURSOR ActiveCursor;
	static bool CtrlKeyActive;
	static HDC deviceContext;
	static WINDOWPLACEMENT wpc; // Saved for restoring last window size and position when exiting fullscreen

	static void ResetCursorPosition(const Window* window);

	// Main message pump handler method
	LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* callingWindow = Window::GetInstance(hwnd);

		switch (message)
		{
		case WM_SETFOCUS:
			focus_callback(callingWindow, true);
			break;
		case WM_KILLFOCUS:
			focus_callback(callingWindow, false);
			break;
		case WM_DESTROY:
			if (callingWindow)
				callingWindow->Dispose();
			PostQuitMessage(0);
			break;
		case WM_MENUCHAR:
			if (LOWORD(wParam) == VK_RETURN)
				return MAKELRESULT(0, MNC_CLOSE);
			return MAKELRESULT(0, MNC_IGNORE);
		case WM_KEYDOWN:
		case WM_KEYUP:
			key_callback(callingWindow, wParam, message);
			break;
		case WM_SYSKEYDOWN:
			if (callingWindow && wParam == S3_KEY_RETURN)
				callingWindow->SetFullScreen(!callingWindow->IsFullScreen());
			break;
		case WM_SIZE:
			resize_callback(callingWindow, LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_MOUSEMOVE:
			cursor_position_callback(callingWindow);
			break;
		default:
			if (callingWindow && message > 512 && message < 527)
				key_callback(callingWindow, wParam, message);
		}

		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	// Returns a struct containing screen pixel format data. Required for window setup.
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

	bool Window::CreateMainWindow()
	{
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = WindowProcedure;
		wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
		wc.lpszClassName = "S3DGE_Win32WindowClass";
		if (!RegisterClass(&wc))
			return 1;

		RECT clientArea;
		clientArea.left = 0;
		clientArea.top = 0;
		clientArea.bottom = _height;
		clientArea.right = _width;
		AdjustWindowRectEx(&clientArea, WS_OVERLAPPEDWINDOW | WS_VISIBLE, false, WS_EX_APPWINDOW);

		HWND window = CreateWindowEx(
			WS_EX_APPWINDOW,
			wc.lpszClassName,
			_title,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			0,
			0,
			clientArea.right - clientArea.left,
			clientArea.bottom - clientArea.top,
			HWND_DESKTOP,
			NULL,
			wc.hInstance,
			NULL);

		if (!window)
		{
			LOG_FATAL("Could not create window!");
			return false;
		}

		Window::SetInstance(window, this);

		ActiveCursor = GetCursor();

		return true;
	}

	bool Window::CreateContext()
	{
		deviceContext = GetDC((HWND)_handle);

		if (!deviceContext)
		{
			LOG_ERROR("Failed getting device context!");
			return false;
		}

		PIXELFORMATDESCRIPTOR pixelFormatDescriptor = GetPixelFormatDescriptor();

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

		HGLRC renderingContext = wglCreateContext(deviceContext);

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

	void Window::SetupContext()
	{
		// Apply basic OpenGL setup
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glFrontFace(GL_CW);
		//glEnable(GL_CULL_FACE);

#ifdef S3_DEBUG
			// Enable the debug callback
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openglCallbackFunction, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
#endif

		LOG_INFO("OpenGL v. ", (char*)glGetString(GL_VERSION));
		LOG_INFO("Renderer: ", (char*)glGetString(GL_RENDERER));
	}

	void Window::Update()
	{
		MSG messages;
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
		{
			if (messages.message == WM_QUIT)
				_isClosed = true;

			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}

		SwapBuffers(deviceContext);
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SetFullScreen(bool fullscreen)
	{
		HWND window = (HWND)_handle;

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
			SetWindowLong(window, GWL_EXSTYLE, WS_EX_APPWINDOW);
			SetWindowPlacement(window, &wpc);
			ShowWindow(window, SW_SHOWDEFAULT);
		}

		SetFocus(window);
		ResetCursorPosition(this);
		_fullScreen = fullscreen;
	}

	void Window::SetVSync(bool vsync)
	{
		typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		cstring extensions = (char*)glGetString(GL_EXTENSIONS);

		if (strstr(extensions, "WGL_EXT_swap_control") == 0)
			return;

		else
		{
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

			if (wglSwapIntervalEXT)
				wglSwapIntervalEXT(vsync);

			this->_vSync = vsync;
		}
	}

	void Window::DestroyContext()
	{
		HGLRC renderingContext;

		if (renderingContext = wglGetCurrentContext())
		{
			deviceContext = wglGetCurrentDC();
			// make the rendering context not current  
			wglMakeCurrent(NULL, NULL);
			// release the device context  
			ReleaseDC((HWND)_handle, deviceContext);
			// delete the rendering context  
			wglDeleteContext(renderingContext);
		}
	}

	static void ResetCursorPosition(const Window* window)
	{
		if (window)
		{
			uint halfWidth = window->GetWidth() / 2;
			uint halfHeight = window->GetHeight() / 2;
			SetCursorPos(halfWidth, halfHeight);
		}
	}

	void resize_callback(Window*const window, const uint width, const uint height)
	{
		if (!window)
			return;

		RECT rect = RECT();
		GetClientRect((HWND)window->_handle, &rect);

		window->_width = rect.right - rect.left;
		window->_height = rect.bottom - rect.top;

		glViewport(0, 0, window->_width, window->_height);
	}

	void cursor_position_callback(const Window*const window)
	{
		if (!window)
			return;

		POINT mousePosition;
		GetCursorPos(&mousePosition);

		InputManager::_mousePosition.x = (float)mousePosition.x;
		InputManager::_mousePosition.y = (float)mousePosition.y;

		uint halfWidth = window->GetWidth() / 2;
		uint halfHeight = window->GetHeight() / 2;

		if (InputManager::_mousePosition.x != halfWidth || InputManager::_mousePosition.y != halfHeight)
		{
			InputManager::_mouseDisplacement.x = (InputManager::_mousePosition.x - halfWidth) / (halfWidth);
			InputManager::_mouseDisplacement.y = (InputManager::_mousePosition.y - halfHeight) / (halfHeight);
			ResetCursorPosition(window);
		}

		SetCursor(NULL);
	}

	void key_callback(const Window*const window, const int key, const int command)
	{
		if (!window)
			return;

		switch (command)
		{
		case WM_LBUTTONDOWN:
		{
			InputManager::_keysDown[S3_KEY_LMB] = true;
			InputManager::_keysClicked[S3_KEY_LMB] = true;
			return;
		}
		case WM_LBUTTONUP:
		{
			InputManager::_keysDown[S3_KEY_LMB] = false;
			return;
		}
		case WM_RBUTTONDOWN:
		{
			InputManager::_keysDown[S3_KEY_RMB] = true;
			InputManager::_keysClicked[S3_KEY_RMB] = true;
			return;
		}
		case WM_RBUTTONUP:
		{
			InputManager::_keysDown[S3_KEY_RMB] = false;
			return;
		}
		case WM_MBUTTONDOWN:
		{
			InputManager::_keysDown[S3_KEY_MMB] = true;
			InputManager::_keysClicked[S3_KEY_MMB] = true;
			return;
		}
		case WM_MBUTTONUP:
		{
			InputManager::_keysDown[S3_KEY_MMB] = false;
			return;
		}
		case WM_XBUTTONDOWN:
		{
			if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
			{
				InputManager::_keysDown[S3_KEY_XBUTTON1] = true;
				InputManager::_keysClicked[S3_KEY_XBUTTON1] = true;
			}
			else
			{
				InputManager::_keysDown[S3_KEY_XBUTTON2] = true;
				InputManager::_keysClicked[S3_KEY_XBUTTON2] = true;
			}
			return;
		}
		case WM_XBUTTONUP:
		{
			if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
				InputManager::_keysDown[S3_KEY_XBUTTON1] = false;
			else
				InputManager::_keysDown[S3_KEY_XBUTTON2] = false;
			return;
		}
		case WM_MOUSEWHEEL:
		{
			short zDelta = (short)GET_WHEEL_DELTA_WPARAM(key);
			if (zDelta > 0)
			{
				InputManager::_keysDown[S3_KEY_MWUP] = true;
				InputManager::_keysClicked[S3_KEY_MWUP] = true;
			}
			if (zDelta < 0)
			{
				InputManager::_keysDown[S3_KEY_MWDOWN] = true;
				InputManager::_keysClicked[S3_KEY_MWDOWN] = true;
			}
			return;
		}
		case WM_KEYDOWN:
			InputManager::_keysDown[key] = true;
			InputManager::_keysClicked[key] = true;
			return;
		case WM_KEYUP:
			InputManager::_keysDown[key] = false;
			return;
		}
	}

	void focus_callback(Window*const window, const bool hasFocus)
	{
		if (window)
			window->_hasFocus = hasFocus;
	}
}