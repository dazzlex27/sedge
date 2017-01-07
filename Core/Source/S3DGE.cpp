/*
===========================================================================
S3DGE.cpp

Implementation of the top level engine functions.
===========================================================================
*/

#include "../Include/S3DGE.h"
#include "Internal/Log.h"

using namespace s3dge;
using namespace graphics;
using namespace audio;

S3DGE::S3DGE()
{
	_state = EngineState::READY;
}

S3DGE::~S3DGE()
{
}

Window* S3DGE::CreateGameWindow(cstring name, uint width, uint height, bool fullscreen, bool vsync)
{
	_window = new Window(name, width, height, fullscreen, vsync);
	return _window;
}

void S3DGE::Run()
{
	LOG_INFO("Application started...");

	_state = EngineState::INITIALIZING;
	LOG_INFO("Initializing components...");
	InitializeInternalSystems();
	InitializeResourceManagers();
	Initialize();
	_state = EngineState::RUNNING;
	LOG_INFO("Running main loop...");
	RunGameLoop();
	_state = EngineState::DISPOSING;
	LOG_INFO("Shutdown initiated...");
	Dispose();
	DisposeResourceManagers();
	DisposeInternalSystems();

	_state = EngineState::DISPOSED;
	LOG_INFO("Application exited...");
}

void S3DGE::RunGameLoop()
{
	uint updates = 0;
	float updateTime = 0.0f;
	uint frames = 0;
	float renderTime = 0.0f;
	_timer->Start();

	// The actual game loop.
	while (!_window->IsClosed())
	{
		_window->Clear();

		// Update input and managers.
		if (_timer->ElapsedS() - updateTime > (1.0f / 60.0f))
		{
			UpdateInput();
			_window->UpdateInputState();
			UpdateResourceManagers();
			++updates;
			updateTime += 1.0f / 60.0f;
		}

		Render();

		++frames;

		_window->Update();

		// Update service information.
		if (_timer->ElapsedS() - renderTime > 1.0f)
		{
			renderTime += 1.0f;
			_fps = frames;
			_ups = updates;
			frames = 0;
			updates = 0;
		}
	}
}

void S3DGE::InitializeInternalSystems()
{
	_timer = new Timer();
	_rng = new RNG();
}

void S3DGE::InitializeResourceManagers()
{
	GraphicsManager::Initialize();
	FontManager::Initialize();
	TextureManager::Initialize();
	SoundManager::Initialize();
}

void S3DGE::UpdateResourceManagers()
{
	SoundManager::Update();
}

void S3DGE::DisposeResourceManagers()
{
	GraphicsManager::Dispose();
	FontManager::Dispose();
	TextureManager::Dispose();
	SoundManager::Dispose();
}

void S3DGE::DisposeInternalSystems()
{
	SafeDelete(_rng);
	SafeDelete(_timer);
	SafeDelete(_window);
}

double S3DGE::GetNextRNG()
{
	return _rng->Next();
}

float S3DGE::GetElapsedMS()
{
	return _timer->ElapsedMS();
}