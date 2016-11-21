#pragma once

#include "Source/S3DGECommon.h"

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
		void StartUp()
		{
			Initialize();
			RunGameLoop();
		}

		uint GetFPS() const { return _fps; }

	protected:
		double GetNextRNG()
		{
			_rng->Next();
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
			uint frames = 0;
			uint updates = 0;
			_timer = new Timer();
			float updateTime = 0.0f;
			float renderTime = 0.0f;

			// The actual game loop.
			while (!_window->IsClosed())
			{
				_window->Clear();

				// Update input.
				if (_timer->ElapsedS() - updateTime > (1.0f / 60.0f))
				{
					_window->UpdateInput();
					UpdateInput();
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

			Dispose();

			LOG_INFO("Application exited");
			getchar();
		}
	};
}