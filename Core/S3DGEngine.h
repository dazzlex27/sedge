/*
===========================================================================
S3DGE.h

Main header file for the engine.
The S3DGEngine class must be inherited in order to build applications using the engine.
===========================================================================
*/

#pragma once

#include "Common.h"

namespace s3dge
{
	struct InitializationToolset
	{
		GraphicsObjectFactorySet GraphicsObjFactorySet;
	};

	class S3DGEngine
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
		S3DGEngine();
		virtual ~S3DGEngine();

		void CreateGameWindow(const char* name, uint width, uint height, bool fullscreen = false, bool vsync = true);

		virtual void Initialize(const InitializationToolset& initToolset) = 0; // Runs upon startup.
		virtual void RunMainLoop(); // Contains main game logic.
		virtual void Dispose() = 0; // Runs upon closing the main window.
		virtual void UpdateLogic() {}
		virtual void Render() {}
	};
}