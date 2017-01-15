/*
===========================================================================
Window.h

Contains basic high-level window management functions.
===========================================================================
*/

#pragma once

#include <map>
#include "CustomTypes.h"
#include "Math/Vector2.h"

namespace s3dge
{
	class Timer;

	namespace graphics
	{
		#define MODE_FULLSCREEN 1
		#define MODE_WINDOWED 0
		#define VSYNC_ON 1
		#define VSYNC_OFF 0
		#define MAX_KEYS 256
		#define MAX_BUTTONS 16

		class Window
		{
		private:
			cstring _title;
			uint _width;
			uint _height;
			bool _isClosed;
			bool _fullScreen;
			bool _vSync;
			math::vec2f _mousePosition;
			bool _keysDown[MAX_KEYS];
			bool _buttonsDown[MAX_BUTTONS];
			bool _keysClicked[MAX_KEYS];
			bool _buttonsClicked[MAX_BUTTONS];
			bool _buttonsDoubleClicked[MAX_BUTTONS];
			Timer* _doubleClickTimers[MAX_BUTTONS];
			float _elapsedDoubleClickThreshold;

			static std::map<void*, Window*> _windowInstances;

		public:
			Window(cstring title, uint width, uint height, bool fullscreen = false, bool vsync = true);
			~Window();

			void Clear();
			void Update();
			void UpdateInputState();
			bool KeyDown(uint key) const;
			bool KeyClicked(uint key) const;
			bool MouseButtonDown(uint button) const;
			bool MouseButtonClicked(uint button) const;
			bool MouseButtonDoubleClicked(uint key) const;

			static void SetHandle(void* handle, Window* window);
			void SetVSync(bool vsync);
			void SetFullScreen(bool fullscreen);

			static Window* GetWindowClassInstance(void* windowInstance);
			inline cstring GetTitle() const { return _title; }
			inline uint GetWidth() const { return _width; }
			inline uint GetHeight() const { return _height; }
			inline bool IsClosed() const { return _isClosed; }
			inline bool IsVSync() const { return _vSync; }
			inline bool IsFullScreen() const { return _fullScreen; }
			inline math::vec2f GetMousePosition() const { return _mousePosition; }

		private:
			bool Initialize();
			void Dispose();
			bool CreateMainWindow();
			void InitializeInput();
			bool CreateContext();
			void SetupContext();

			friend void resize_callback(Window* window, uint width, uint height);
			friend void key_callback(Window* window, int key, int command);
			friend void mousebutton_callback(Window* window, int key, int command);

			Window(const Window& tRef) = delete;				// Disable copy constructor.
			Window& operator = (const Window& tRef) = delete;	// Disable assignment operator.
		};
	}
}