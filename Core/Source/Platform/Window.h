/*
===========================================================================
Window.h

Contains basic high-level window management functions.
===========================================================================
*/

#pragma once

#include <map>
#include "CustomTypes.h"

namespace s3dge
{
	class Timer;

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
		void* _handle;

		static std::map<void*, Window*> Instances;

	public:
		Window(cstring title, const uint width, const uint height, const bool fullscreen = false, const bool vsync = true);
		~Window();

		bool Initialize();
		void Update();
		void Clear();
		void Dispose();

		inline cstring GetTitle() const { return _title; }
		inline uint GetWidth() const { return _width; }
		inline uint GetHeight() const { return _height; }
		inline bool IsClosed() const { return _isClosed; }
		inline bool IsVSync() const { return _vSync; }
		inline bool HasFocus() const { return _hasFocus; }
		inline bool IsFullScreen() const { return _fullScreen; }

		static Window* GetInstance(void*const handle);

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

		friend void resize_callback(Window*const window, const uint width, const uint height);
		friend void focus_callback(Window*const window, const bool hasFocus);

		Window(const Window& tRef) = delete;				// Disable copy constructor.
		Window& operator = (const Window& tRef) = delete;	// Disable assignment operator.
	};
}