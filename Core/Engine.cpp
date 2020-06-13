/*
===========================================================================
sedge.cpp

Implementation of the top level engine functions.
===========================================================================
*/

#include "Engine.h"
#include "System/Logger.h"

using namespace sedge;

Engine::Engine()
{
	_runTimer = new Stopwatch();
	Window::InitializeLibrary();
}

Engine::~Engine()
{
	Window::DisposeLibrary();
	SafeDelete(_runTimer);
}

void Engine::CreateGameWindow(const char* name, uint width, uint height, bool fullscreen, bool vsync)
{
	if (!MainWindow)
	{
		MainWindow = new Window(name, width, height, fullscreen, vsync);

		if (!MainWindow->Initialize())
		{
			LOG_FATAL("Could not initialize window!");
		}
	}
}

void Engine::Run()
{
	LOG_INFO("Application started...");

	LOG_INFO("Initializing components...");
	Initialize(_initToolset);
	LOG_INFO("Running main loop...");
	RunMainLoop();
	LOG_INFO("Shutdown initiated...");
	Dispose();

	LOG_INFO("Application exited...");
}

void Engine::RunMainLoop()
{
	uint updates = 0;
	float updateTime = 0.0f;
	uint frames = 0;
	float renderTime = 0.0f;
	_runTimer->Start();

	// The actual game loop.
	while (MainWindow != nullptr && !MainWindow->IsClosed())
	{
		MainWindow->Clear();

		// Update input and managers.
		if (_runTimer->ElapsedS() - updateTime > (1.0f / 60.0f))
		{
			UpdateLogic();
			MainWindow->UpdateContextState();

			++updates;
			updateTime += 1.0f / 60.0f;
		}

		Render();
		MainWindow->UpdateWindowState();

		frames++;

		// Update service information.
		if (_runTimer->ElapsedS() - renderTime > 1.0f)
		{
			renderTime += 1.0f;
			_fps = frames;
			frames = 0;
			updates = 0;
		}
	}
}