/*
===========================================================================
S3DGE.h

Main header file for the engine.
The S3DGEngine class must be inherited in order to build applications using the engine.
===========================================================================
*/

#pragma once

#include "../Source/Common.h"

namespace s3dge
{
	enum ENGINE_STATE
	{
		READY,
		INITIALIZING,
		RUNNING,
		DISPOSING,
		DISPOSED
	};

	class S3DGEngine
	{
	private:
		ENGINE_STATE _state;
		Timer* _timer;
		RNG* _rng;
		uint _fps;
		uint _ups;

	protected:
		S3DGEngine();
		virtual ~S3DGEngine();
		Window* MainWindow;

	public:
		voID Run();
		inline uint GetFPS() const { return _fps; }
		inline ENGINE_STATE GetEngineState() const { return _state; }

	protected:
		voID CreateGameWindow(const char* name, uint wIDth, uint height, bool fullscreen = false, bool vsync = true);
		double GetNextRNG();
		float GetElapsedMS();

		virtual voID Initialize() = 0; // Runs upon startup.
		virtual voID Update() = 0; // Runs 60 times a second.
		virtual voID Render() = 0; // Runs the number of times the current frame rate.
		virtual voID Dispose() = 0; // Runs upon closing the main window.

	private:
		voID RunGameLoop(); // Starts the actual gameloop
		voID InitializeInternalSystems();
		voID InitializeResourceManagers();
		voID UpdateResourceManagers();
		voID DisposeResourceManagers();
		voID DisposeInternalSystems();
	};
}