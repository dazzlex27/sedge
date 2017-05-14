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
		Window* WindowInstance;

	public:
		void Run();
		inline uint GetFPS() const { return _fps; }
		inline ENGINE_STATE GetEngineState() const { return _state; }

	protected:
		void CreateGameWindow(cstring name, uint width, uint height, bool fullscreen = false, bool vsync = true);
		double GetNextRNG();
		float GetElapsedMS();

		virtual void Initialize() = 0; // Runs upon startup.
		virtual void UpdateInput() = 0; // Runs 60 times a second.
		virtual void Render() = 0; // Runs the number of times the current frame rate.
		virtual void Dispose() = 0; // Runs upon closing the main window.

	private:
		void RunGameLoop(); // Starts the actual gameloop
		void InitializeInternalSystems();
		void InitializeResourceManagers();
		void UpdateResourceManagers();
		void DisposeResourceManagers();
		void DisposeInternalSystems();
	};
}