/*
===========================================================================
Win32Window.h

Main Win32 implementation file.
===========================================================================
*/

#pragma once

#include <Windows.h>
#include "System/Logger.h"
#include "Platform/Window.h"
#include "Win32InputKeys.h"
#include "System/InputManager.h"
#include "Graphics/GraphicsAPI.h"

namespace sedge
{
	static HCURSOR ActiveCursor;
	static bool CtrlKeyActive;
	static HDC deviceContext;
	static WINDOWPLACEMENT wpc; // Saved for restoring last window size and position when exiting fullscreen

	static void ResetCursorPosition(const Window*const window);

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
		wc.lpszClassName = "sedge_Win32WindowClass";
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
			_title.c_str(),
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

		if (!GraphicsAPI::Initialize())
		{
			LOG_ERROR("Failed to initialize GraphicsAPI!");
			return false;
		}

		return true;
	}
	
	void Window::UpdateWindowState()
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
	
	void Window::SetFullScreen(const bool fullscreen)
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

	void Window::SetVSync(const bool vsync)
	{
		typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		const char* extensions = GraphicsAPI::GetExtensions();

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

		GraphicsAPI::Dispose();
	}

	static void ResetCursorPosition(const Window*const window)
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

		GraphicsAPI::SetViewPort(0, 0, window->GetWidth(), window->GetHeight());
	}

	void cursor_position_callback(Window*const window)
	{
		if (!window)
			return;

		POINT mousePosition;
		GetCursorPos(&mousePosition);

		window->_inputManager->_mousePosition.x = (float)mousePosition.x;
		window->_inputManager->_mousePosition.y = (float)mousePosition.y;

		uint halfWidth = window->GetWidth() / 2;
		uint halfHeight = window->GetHeight() / 2;

		if (window->_inputManager->_mousePosition.x != halfWidth || window->_inputManager->_mousePosition.y != halfHeight)
		{
			window->_inputManager->_mouseDisplacement.x = (window->_inputManager->_mousePosition.x - halfWidth) / (halfWidth);
			window->_inputManager->_mouseDisplacement.y = (window->_inputManager->_mousePosition.y - halfHeight) / (halfHeight);
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
			window->_inputManager->_keysDown[S3_KEY_LMB] = true;
			window->_inputManager->_keysClicked[S3_KEY_LMB] = true;
			return;
		}
		case WM_LBUTTONUP:
		{
			window->_inputManager->_keysDown[S3_KEY_LMB] = false;
			return;
		}
		case WM_RBUTTONDOWN:
		{
			window->_inputManager->_keysDown[S3_KEY_RMB] = true;
			window->_inputManager->_keysClicked[S3_KEY_RMB] = true;
			return;
		}
		case WM_RBUTTONUP:
		{
			window->_inputManager->_keysDown[S3_KEY_RMB] = false;
			return;
		}
		case WM_MBUTTONDOWN:
		{
			window->_inputManager->_keysDown[S3_KEY_MMB] = true;
			window->_inputManager->_keysClicked[S3_KEY_MMB] = true;
			return;
		}
		case WM_MBUTTONUP:
		{
			window->_inputManager->_keysDown[S3_KEY_MMB] = false;
			return;
		}
		case WM_XBUTTONDOWN:
		{
			if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
			{
				window->_inputManager->_keysDown[S3_KEY_XBUTTON1] = true;
				window->_inputManager->_keysClicked[S3_KEY_XBUTTON1] = true;
			}
			else
			{
				window->_inputManager->_keysDown[S3_KEY_XBUTTON2] = true;
				window->_inputManager->_keysClicked[S3_KEY_XBUTTON2] = true;
			}
			return;
		}
		case WM_XBUTTONUP:
		{
			if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
				window->_inputManager->_keysDown[S3_KEY_XBUTTON1] = false;
			else
				window->_inputManager->_keysDown[S3_KEY_XBUTTON2] = false;
			return;
		}
		case WM_MOUSEWHEEL:
		{
			short zDelta = (short)GET_WHEEL_DELTA_WPARAM(key);
			if (zDelta > 0)
			{
				window->_inputManager->_keysDown[S3_KEY_MWUP] = true;
				window->_inputManager->_keysClicked[S3_KEY_MWUP] = true;
			}
			if (zDelta < 0)
			{
				window->_inputManager->_keysDown[S3_KEY_MWDOWN] = true;
				window->_inputManager->_keysClicked[S3_KEY_MWDOWN] = true;
			}
			return;
		}
		case WM_KEYDOWN:
			window->_inputManager->_keysDown[key] = true;
			window->_inputManager->_keysClicked[key] = true;
			return;
		case WM_KEYUP:
			window->_inputManager->_keysDown[key] = false;
			return;
		}
	}

	void focus_callback(Window*const window, const bool hasFocus)
	{
		if (window)
			window->_hasFocus = hasFocus;
	}
}