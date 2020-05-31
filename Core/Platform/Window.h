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

namespace s3dge
{
	class InputManager;
	class SoundManager;
	struct Vector2;

	class Window
	{
	private:
		std::string _title;
		uint _width;
		uint _height;
		bool _isClosed;
		bool _fullScreen;
		bool _vSync;
		bool _hasFocus;
		void* _handle;
		InputManager* _inputManager;
		SoundManager* _soundManager;

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

		static Window*const GetInstance(void*const handle);

		void SetVSync(const bool vsync);
		void SetFullScreen(const bool fullscreen);
		static void SetInstance(void*const handle, Window*const instance);

	private:
		bool CreateMainWindow();
		bool CreateContext();
		void SetupContext();
		void DestroyContext();

		void* GetHandle() const;
		void SetHandle(void*const handle);

		Window(const Window& tRef) = delete;				// Disable copy constructor.
		Window& operator = (const Window& tRef) = delete;	// Disable assignment operator.

		friend void cursor_position_callback(Window*const window);
		friend void key_callback(const Window*const window, const int key, const int command);
		friend void resize_callback(Window*const window, const uint width, const uint height);
		friend void focus_callback(Window*const window, const bool hasFocus);
	};
}