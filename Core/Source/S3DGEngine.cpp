/*
===========================================================================
S3DGE.cpp

Implementation of the top level engine functions.
===========================================================================
*/

#include "../Include/S3DGEngine.h"
#include "System/Logger.h"
#include "System/Execution.h"

using namespace s3dge;

S3DGEngine::S3DGEngine()
{
	_state = ENGINE_STATE::READY;
	_runTimer = new Stopwatch();
}

S3DGEngine::~S3DGEngine()
{
	SafeDelete(_runTimer);
}

void S3DGEngine::CreateGameWindow(const char* name, uint width, uint height, bool fullscreen, bool vsync)
{
	if (!MainWindow)
	{
		MainWindow = new Window(name, width, height, fullscreen, vsync);

		if (!MainWindow->Initialize())
		{
			LOG_FATAL("Could not initialize window!");
			TerminateProgram("Could not initialize window!");
		}
	}
}

void S3DGEngine::Run()
{
	LOG_INFO("Application started...");

	_state = ENGINE_STATE::INITIALIZING;
	LOG_INFO("Initializing components...");
	Initialize(_initToolset);
	_state = ENGINE_STATE::RUNNING;
	LOG_INFO("Running main loop...");
	RunMainLoop();
	_state = ENGINE_STATE::DISPOSING;
	LOG_INFO("Shutdown initiated...");
	Dispose();
	_state = ENGINE_STATE::DISPOSED;

	LOG_INFO("Application exited...");
}

void S3DGEngine::RunMainLoop()
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