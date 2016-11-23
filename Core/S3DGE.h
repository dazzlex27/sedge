#pragma once

#include "Source/Common.h"

namespace s3dge
{
	class S3DGE
	{
	private:
		Graphics::Window* _window;
		Timer* _timer;
		RNG* _rng;
		uint _fps;
		uint _ups;

	protected:
		S3DGE()
		{
		}

		virtual ~S3DGE()
		{
			SafeDelete(_window);
			SafeDelete(_timer);
			SafeDelete(_rng);
		}

		Graphics::Window* CreateGameWindow(cstring name, uint width, uint height, bool fullscreen = false, bool vsync = true)
		{
			_window = new Graphics::Window(name, width, height, fullscreen, vsync);
			return _window;
		}

	public:
		void Run()
		{
			LOG_INFO("Application started...");

			LOG_INFO("Initializing components...");
			InitializeInternalSystems();
			Initialize();
			LOG_INFO("Running main loop...");
			RunGameLoop();

			LOG_INFO("Shutdown initiated...");
			Dispose();
			ShutdownInternalSystems();

			LOG_INFO("Application exited...");
		}

		uint GetFPS() const { return _fps; }

	protected:
		double GetNextRNG()
		{
			_rng->Next();
		}

		float GetElapsedMS()
		{
			return _timer->ElapsedMS();
		}

		// Runs upon startup.
		virtual void Initialize() = 0;
		// Runs 60 times a second.
		virtual void UpdateInput() = 0;
		// Runs the number of times the current frame rate.
		virtual void Render() = 0;
		// Runs upon closing the main window.
		virtual void Dispose() = 0;

	private:
		void RunGameLoop()
		{
			uint updates = 0;
			float updateTime = 0.0f;
			uint frames = 0;
			float renderTime = 0.0f;

			// The actual game loop.
			while (!_window->IsClosed())
			{
				_window->Clear();

				// Update input.
				if (_timer->ElapsedS() - updateTime > (1.0f / 60.0f))
				{
					UpdateInput();
					_window->UpdateInputState();
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

		void InitializeInternalSystems()
		{
			_rng = new RNG();
			_timer = new Timer();
		}

		void ShutdownInternalSystems()
		{
			SafeDelete(_rng);
			SafeDelete(_timer);
			SafeDelete(_window);
		}
	};
}