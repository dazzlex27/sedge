/*
===========================================================================
Window.h

Contains basic high-level window management functions.
===========================================================================
*/

#pragma once

#include <map>
#include <string>
#include <CustomTypes.h>

namespace sedge
{
	class InputManager;
	struct Vector2;

	class Window
	{
	private:
		std::string _title;
		int _posX;
		int _posY;
		int _width;
		int _height;
		bool _isClosed;
		bool _fullScreen;
		bool _vSync;
		bool _hasFocus;
		void* _handle;
		InputManager* _inputManager;

		static std::map<void*, Window*> Instances;

	public:
		Window(const char* title, const uint width, const uint height, const bool fullscreen = false, const bool vsync = true);
		~Window();

		bool Initialize();
		void UpdateContextState();
		void UpdateWindowState();
		void Clear();

		inline const char* GetTitle() const { return _title.c_str(); }
		inline uint GetWidth() const { return _width; }
		inline uint GetHeight() const { return _height; }
		inline bool IsClosed() const { return _isClosed; }
		inline bool IsVSync() const { return _vSync; }
		inline bool HasFocus() const { return _hasFocus; }
		inline bool IsFullScreen() const { return _fullScreen; }
		
		InputManager*const GetInputManager() { return _inputManager; }

		static bool InitializeLibrary();
		static void DisposeLibrary();

		static Window*const GetInstance(void*const handle);
		static void UpdateWindowFocus(Window* const window, const bool hasFocus);
		static void UpdateWindowCursor(Window* const window, const double xPos, const double yPos);
		static void UpdateKeyState(Window* const window, const uint key, const bool isPressed);

		void SetSize(int width, int height);
		void SetVSync(const bool vsync);
		void SetFullScreen(const bool fullscreen);
		static void SetInstance(void*const handle, Window*const instance);
		static void RemoveInstance(void* const handle);

	private:
		void* GetHandle() const;
		void SetHandle(void*const handle);

		Window(const Window& tRef) = delete;				// Disable copy constructor.
		Window& operator = (const Window& tRef) = delete;	// Disable assignment operator.

		static void WindowErrorCallback(int error, const char* description);

		static void WindowKeyCallback(Window* const window, const bool key);


		//friend void key_callback(const Window*const window, const int key, const int command);
		//friend void resize_callback(Window*const window, const uint width, const uint height);

	};
}