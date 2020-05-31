/*
===========================================================================
Window.cpp

Contains basic high-level window management functions.
===========================================================================
*/

#include "Window.h"
#include "KeyCodes.h"
#include "System/Logger.h"
#include "System/MemoryManagement.h"
#include "System/Stopwatch.h"
#include "Graphics/GraphicsAPI.h"
#include "System/InputManager.h"
#include "Audio/SoundManager.h"

using namespace sedge;

std::map<void*, Window*> Window::Instances;

Window::Window(const char* title, const uint width, const uint height, const bool fullscreen, const bool vsync)
	: _title(title), _width(width), _height(height), _fullScreen(fullscreen), _vSync(vsync), _isClosed(false)
{
	_inputManager = new InputManager();
	_soundManager = new SoundManager();
}

Window::~Window()
{
	DestroyContext();
	SafeDelete(_inputManager);
	SafeDelete(_soundManager);
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

void Window::SetupContext()
{
	GraphicsAPI::EnableDepthTesting();
	GraphicsAPI::EnableBlending();
	GraphicsAPI::EnableFaceCulling();
	GraphicsAPI::SetStandartBlending();
	GraphicsAPI::SetWindingOrder(CounterClockwise);

	LOG_INFO("Version: ", GraphicsAPI::GetVersion());
	LOG_INFO("Rendering device: ", GraphicsAPI::GetRenderingDevice());
}

void Window::Clear()
{
	GraphicsAPI::Clear();
}

void Window::UpdateContextState()
{
	_inputManager->Update();
	_soundManager->Update();
}

void* Window::GetHandle() const
{
	return _handle;
}

void Window::SetHandle(void*const handle)
{
	_handle = handle;
}

// Returns a window instance of a specified index
Window*const Window::GetInstance(void*const handle)
{
	return Instances[handle];
}

// Inserts a window instance into a static window collection
void Window::SetInstance(void*const handle, Window*const instance)
{
	Instances[handle] = instance;
	if (instance)
		instance->SetHandle(handle);
}