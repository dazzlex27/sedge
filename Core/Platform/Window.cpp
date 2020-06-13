/*
===========================================================================
Window.cpp

Contains basic high-level window management functions.
===========================================================================
*/

#include "Graphics/GraphicsAPI.h"
#include "Window.h"
#include "KeyCodes.h"
#include "System/Logger.h"
#include "System/MemoryManagement.h"
#include "System/Stopwatch.h"
#include "System/InputManager.h"
#include "GLFW/glfw3.h"

using namespace sedge;

std::map<void*, Window*> Window::Instances;

static void focus_callback(GLFWwindow* window, int focus);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void window_size_callback(GLFWwindow* window, int width, int height);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Window::Window(const char* title, const uint width, const uint height, const bool fullscreen, const bool vsync)
	: _title(title), 
	_width(width), 
	_height(height), 
	_fullScreen(fullscreen), 
	_vSync(vsync), 
	_isClosed(false), 
	_handle(nullptr), 
	_hasFocus(false)
{
	_inputManager = new InputManager();
}

Window::~Window()
{
	RemoveInstance(_handle);

	GraphicsAPI::Dispose();
	glfwDestroyWindow((GLFWwindow*)_handle);

	SafeDelete(_inputManager);
}

bool Window::Initialize()
{
	GLFWwindow* window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
	if (!window)
	{
		LOG_ERROR("Failed to create window ", _title);
		return false;
	}

	_handle = window;
	Window::SetInstance(window, this);

	glfwMakeContextCurrent(window);

	const bool contextCreated = GraphicsAPI::Initialize();
	if (!contextCreated)
	{
		LOG_FATAL("Could not create context!");
		return false;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowFocusCallback(window, focus_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	GraphicsAPI::EnableDepthTesting();
	GraphicsAPI::EnableBlending();
	GraphicsAPI::EnableFaceCulling();
	GraphicsAPI::SetStandartBlending();
	GraphicsAPI::SetWindingOrder(CounterClockwise);

	LOG_INFO("Version: ", GraphicsAPI::GetVersion());
	LOG_INFO("Rendering device: ", GraphicsAPI::GetRenderingDevice());

	SetFullScreen(_fullScreen);
	SetVSync(_vSync);

	return true;
}

void Window::SetVSync(const bool vsync)
{
	_vSync = vsync;
	if (_vSync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

void Window::UpdateWindowState()
{
	glfwSwapBuffers((GLFWwindow*)_handle);
	glfwPollEvents();
}

void Window::Clear()
{
	GraphicsAPI::Clear();
}

void Window::UpdateContextState()
{
	_inputManager->Update();
}

void* Window::GetHandle() const
{
	return _handle;
}

void Window::SetHandle(void*const handle)
{
	_handle = handle;
}

bool Window::InitializeLibrary()
{
	if (!glfwInit())
	{
		LOG_FATAL("Could not initialize the window library!");
		return false;
	}

	glfwSetErrorCallback(WindowErrorCallback);

	return true;
}

void Window::DisposeLibrary()
{
	glfwTerminate();
}

void Window::WindowErrorCallback(int error, const char* description)
{
	LOG_ERROR("glfw error: ", error, "description: ", description);
}

// Returns a window instance of a specified index
Window*const Window::GetInstance(void*const handle)
{
	return Instances[handle];
}

void Window::UpdateWindowFocus(Window* const window, const bool hasFocus)
{
	window->_hasFocus = hasFocus;
}

void Window::UpdateWindowCursor(Window* const window, const double xPos, const double yPos)
{
	window->_inputManager->UpdateCursorPosition(xPos, yPos);
}

void Window::UpdateKeyState(Window* const window, const uint key, const bool isPressed)
{
	window->_inputManager->UpdateKeyState(key, isPressed);
}

void Window::SetFullScreen(const bool fullscreen)
{
	_fullScreen = fullscreen;

	GLFWwindow* window = (GLFWwindow*)_handle;

	if (!fullscreen)
	{
		if (glfwGetWindowMonitor(window))
		{
			glfwSetWindowMonitor(window, NULL,
				_posX, _posY,
				_width, _height, 0);
		}
	}
	else
	{
		auto monitor = glfwGetPrimaryMonitor();
		if (monitor)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwGetWindowPos(window, &_posX, &_posY);
			glfwGetWindowSize(window, &_width, &_height);
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
	}
}

// Inserts a window instance into a static window collection
void Window::SetInstance(void*const handle, Window*const instance)
{
	Instances[handle] = instance;
	if (instance)
		instance->SetHandle(handle);
}

void Window::RemoveInstance(void* const handle)
{
	Instances.erase(handle);
}

static void focus_callback(GLFWwindow* window, int focused)
{
	Window* instance = Window::GetInstance(window);

	const bool isFocused = focused == GLFW_TRUE;

	Window::UpdateWindowFocus(instance, isFocused);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window* instance = Window::GetInstance(window);

	Window::UpdateWindowCursor(instance, xpos, ypos);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!window)
		return;

	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

	Window* instance = Window::GetInstance(window);

	if (key == GLFW_KEY_ENTER && mods == GLFW_MOD_ALT)
	{
		instance->SetFullScreen(!instance->IsFullScreen());
		return;
	}

	switch (action)
	{
		case GLFW_PRESS:
		{
			instance->GetInputManager()->UpdateKeyState(key, true);
			break;
		}
		case GLFW_RELEASE:
		{
			instance->GetInputManager()->UpdateKeyState(key, false);
			break;
		}
	}
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
	Window* instance = Window::GetInstance(window);
	instance->SetSize(width, height);
}

void Window::SetSize(int width, int height)
{
	_width = width;
	_height = height;

	GraphicsAPI::SetViewPort(0, 0, _width, _height);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//switch (button)
	//{
	//case GLFW_MOUSE_BUTTON_1:
	//{
	//	window->_inputManager->_keysDown[S3_KEY_LMB] = false;
	//	return;
	//}
	//case WM_RBUTTONDOWN:
	//{
	//	window->_inputManager->_keysDown[S3_KEY_RMB] = true;
	//	window->_inputManager->_keysClicked[S3_KEY_RMB] = true;
	//	return;
	//}
	//case WM_RBUTTONUP:
	//{
	//	window->_inputManager->_keysDown[S3_KEY_RMB] = false;
	//	return;
	//}
	//case WM_MBUTTONDOWN:
	//{
	//	window->_inputManager->_keysDown[S3_KEY_MMB] = true;
	//	window->_inputManager->_keysClicked[S3_KEY_MMB] = true;
	//	return;
	//}
	//case WM_MBUTTONUP:
	//{
	//	window->_inputManager->_keysDown[S3_KEY_MMB] = false;
	//	return;
	//}
	//case WM_XBUTTONDOWN:
	//{
	//	if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
	//	{
	//		window->_inputManager->_keysDown[S3_KEY_XBUTTON1] = true;
	//		window->_inputManager->_keysClicked[S3_KEY_XBUTTON1] = true;
	//	}
	//	else
	//	{
	//		window->_inputManager->_keysDown[S3_KEY_XBUTTON2] = true;
	//		window->_inputManager->_keysClicked[S3_KEY_XBUTTON2] = true;
	//	}
	//	return;
	//}
	//case WM_XBUTTONUP:
	//{
	//	if (GET_XBUTTON_WPARAM(key) == XBUTTON1)
	//		window->_inputManager->_keysDown[S3_KEY_XBUTTON1] = false;
	//	else
	//		window->_inputManager->_keysDown[S3_KEY_XBUTTON2] = false;
	//	return;
	//}
	//}
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* instance = Window::GetInstance(window);

	if (yoffset > 0)
		instance->GetInputManager()->UpdateKeyState(S3_KEY_MWUP, true);
	if (yoffset < 0)
		instance->GetInputManager()->UpdateKeyState(S3_KEY_MWDOWN, true);
}