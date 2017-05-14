/*
===========================================================================
Window.h

Contains basic high-level window management functions.
===========================================================================
*/

#pragma once

#include <map>
#include "CustomTypes.h"
#include "Math/Point2D.h"

namespace s3dge
{
	class Timer;

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
		bool _hasFocus;
		Point2D _mousePosition;
		bool _keysDown[MAX_KEYS];
		bool _buttonsDown[MAX_BUTTONS];
		bool _keysClicked[MAX_KEYS];
		bool _buttonsClicked[MAX_BUTTONS];
		bool _buttonsDoubleClicked[MAX_BUTTONS];
		Timer* _doubleClickTimers[MAX_BUTTONS];
		float _elapsedDoubleClickThreshold;
		void* _handle;

		static std::map<void*, Window*> Instances;

	public:
		Window(cstring title, uint width, uint height, bool fullscreen = false, bool vsync = true);
		~Window();

		bool Initialize();
		void Dispose();

		// This method is triggered every frame
		void Clear();
		// This method is triggered every frame
		void Update();
		// This method is triggered once every 1/60 of a second.
		// Resets all click and double-click states.
		// Also resets mouse wheel rotation state
		void UpdateInputState();
		bool KeyDown(uint key) const;
		bool KeyClicked(uint key) const;
		bool MouseButtonDown(uint button) const;
		bool MouseButtonClicked(uint button) const;
		bool MouseButtonDoubleClicked(uint key) const;

		inline cstring GetTitle() const { return _title; }
		inline uint GetWidth() const { return _width; }
		inline uint GetHeight() const { return _height; }
		inline bool IsClosed() const { return _isClosed; }
		inline bool IsVSync() const { return _vSync; }
		inline bool HasFocus() const { return _hasFocus; }
		inline bool IsFullScreen() const { return _fullScreen; }
		inline Point2D GetMousePosition() const { return _mousePosition; }

		static Window* GetInstance(void* handle);

		void SetVSync(bool vsync);
		void SetFullScreen(bool fullscreen);
		static void SetInstance(void* handle, Window* instance);

	private:
		bool CreateMainWindow();
		void InitializeInput();
		bool CreateContext();
		void SetupContext();
		void DestroyContext();

		void* GetHandle();
		void SetHandle(void* handle);


		friend void resize_callback(Window* window, uint width, uint height);
		friend void key_callback(Window* window, int key, int command);
		friend void mousebutton_callback(Window* window, int key, int command);
		friend void focus_callback(Window* window, bool hasFocus);

		Window(const Window& tRef) = delete;				// Disable copy constructor.
		Window& operator = (const Window& tRef) = delete;	// Disable assignment operator.
	};
}