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

	return true;
}

Window::~Window()
{
	Dispose();
}

void Window::Dispose()
{
	DestroyContext();
}

void* Window::GetHandle() const
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