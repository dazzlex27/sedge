#pragma once

#include <vector>
#include <map>
#include <GL/glew.h>
#include "CustomTypes.h"
#include "Internal/Log.h"
#include "Maths/vec2.h"
#include "Platforms/Windows/WindowsKeys.h"
#include "Graphics/Textures/TextureManager.h"
#include "Graphics/Fonts/FontManager.h"

namespace s3dge
{
	namespace Graphics
	{
		class Window
		{
			#define MODE_FULLSCREEN 1
			#define MODE_WINDOWED 0
			#define MAX_KEYS 256
			#define MAX_BUTTONS 16

		private:
			cstring _title;
			uint _width;
			uint _height;
			bool _isClosed;
			bool _fullScreen;
			bool _vSync;
			Maths::vec2f _mousePosition;
			bool _keysDown[MAX_KEYS];
			bool _buttonsDown[MAX_BUTTONS];
			bool _keysClicked[MAX_KEYS];
			bool _buttonsClicked[MAX_BUTTONS];

			static std::map<void*, Window*> _windowInstances;

		public:
			Window(cstring title,  uint width, uint height, bool fullscreen = false, bool vsync = true);
			~Window();

			void Clear();
			void Update();
			void UpdateInputState();
			bool KeyDown(uint key) const;
			bool KeyClicked(uint key) const;
			bool KeyDoubleClicked(uint key) const;
			bool MouseButtonDown(uint button) const;
			bool MouseButtonClicked(uint button) const;
			
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
			inline Maths::vec2f GetMousePosition() const { return _mousePosition; }

		private:
			bool InitializeWindow();
			void UpdateWindow();

			friend void resize_callback(Window* window, uint width, uint height);
			friend void key_callback(Window* window, int key, int command);
			friend void mousebutton_callback(Window* window, int key, int command);

			Window(const Window& tRef) = delete;				// Disable copy constructor.
			Window& operator = (const Window& tRef) = delete;	// Disable assignment operator.
		};
	}
}