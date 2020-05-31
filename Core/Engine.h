/*
===========================================================================
sedge.h

Main header file for the engine.
The sedgengine class must be inherited in order to build applications using the engine.
===========================================================================
*/

#pragma once

#include "Common.h"

namespace sedge
{
	struct InitializationToolset
	{
		GraphicsObjectFactorySet GraphicsObjFactorySet;
	};

	class Engine
	{
	protected:
		Window* MainWindow;

	private:
		uint _fps;
		Stopwatch* _runTimer;

		InitializationToolset _initToolset;

	public:
		void Run();
		inline uint GetFPS() const { return _fps; }

	protected:
		Engine();
		virtual ~Engine();

		void CreateGameWindow(const char* name, uint width, uint height, bool fullscreen = false, bool vsync = true);

		virtual void Initialize(const InitializationToolset& initToolset) = 0; // Runs upon startup.
		virtual void RunMainLoop(); // Contains main game logic.
		virtual void Dispose() = 0; // Runs upon closing the main window.
		virtual void UpdateLogic() {}
		virtual void Render() {}
	};
}