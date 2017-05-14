/*
===========================================================================
Window.cpp

Contains basic high-level window management functions.
===========================================================================
*/

#include "Window.h"
#include "KeyCodes.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"
#include "System/Timer.h"

using namespace s3dge;

std::map<void*, Window*> Window::Instances;

Window::Window(cstring title, uint width, uint height, bool fullscreen, bool vsync)
	: _title(title), _width(width), _height(height), _fullScreen(fullscreen), _vSync(vsync), _isClosed(false)
{
}

bool Window::Initialize()
{
	if (!CreateMainWindow())
	{
		LOG_FATAL("Could not create window!");
		return false;
	}

	if (!CreateContext())
	{
		LOG_FATAL("Could not create context!");
		return false;
	}

	SetupContext();
	SetFullScreen(_fullScreen);
	SetVSync(_vSync);
	InitializeInput();

	return true;
}

void Window::InitializeInput()
{
	memset(&_keysDown, 0, sizeof(_keysDown));
	memset(&_keysClicked, 0, sizeof(_keysClicked));
	memset(&_buttonsDown, 0, sizeof(_buttonsDown));
	memset(&_buttonsClicked, 0, sizeof(_buttonsClicked));
	memset(&_buttonsDoubleClicked, 0, sizeof(_buttonsDoubleClicked));
	for (int i = 0; i < MAX_BUTTONS; ++i)
		_doubleClickTimers[i] = new Timer();

	_elapsedDoubleClickThreshold = 1.0f;
}

Window::~Window()
{
	Dispose();
}

void Window::Dispose()
{
	DestroyContext();

	for (int i = 0; i < MAX_BUTTONS; ++i)
		SafeDelete(_doubleClickTimers[i]);
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

void* Window::GetHandle()
{
	return _handle;
}

void Window::SetHandle(void* handle)
{
	_handle = handle;
}

// Returns a window instance of a specified index
Window* Window::GetInstance(void* handle)
{
	return Instances[handle];
}

// Inserts a window instance into a static window collection
void Window::SetInstance(void* handle, Window* instance)
{
	Instances[handle] = instance;
	if (instance != nullptr)
		instance->SetHandle(handle);
}