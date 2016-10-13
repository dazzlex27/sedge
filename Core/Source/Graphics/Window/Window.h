#pragma once

#include <vector>
#include <map>
#include <GL/glew.h>
#include "S3DGETypes.h"
#include "../Internal/Log.h"
#include "Maths/vec2.h"
#include "Platforms/Windows/WindowsKeys.h"
#include "Graphics/Textures/TextureManager.h"

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
			cstring m_Title;
			uint m_Width;
			uint m_Height;
			bool m_IsClosed;
			bool m_FullScreen;
			bool m_VSync;
			Maths::vec2f m_Mouse;
			bool m_Keys[MAX_KEYS];
			bool m_Buttons[MAX_BUTTONS];

			static std::map<void*, Window*> m_WindowInstances;

		public:
			Window(cstring title,  uint width, uint height, bool fullscreen = false, bool vsync = true);
			~Window();

			void Clear();
			void Update();
			void UpdateInput();
			bool KeyPressed(uint key) const;
			bool KeyClicked(uint key) const;
			bool MouseButtonPressed(uint button) const;
			bool MouseButtonClicked(uint button) const;
			
			static void SetHandle(void* handle, Window* window);
			void SetVSync(bool vsync);
			void SetFullScreen(bool fullscreen);

			static Window* GetWindowClassInstance(void* windowInstance);
			inline cstring GetTitle() const { return m_Title; }
			inline uint GetWidth() const { return m_Width; }
			inline uint GetHeight() const { return m_Height; }
			inline bool IsClosed() const { return m_IsClosed; }
			inline bool IsVSync() const { return m_VSync; }
			inline bool IsFullScreen() const { return m_FullScreen; }
			inline Maths::vec2f GetMousePosition() const { return m_Mouse; }

		private:
			bool InitializeWindow();
			void UpdateWindow();

			friend void resize_callback(Window* window, uint width, uint height);
			friend void key_callback(Window* window, int key, int command);
			friend void mousebutton_callback(Window* window, int key, int command);

			Window(void);
			Window(const Window& tRef) = delete;				// Disable copy constructor.
			Window& operator = (const Window& tRef) = delete;	// Disable assignment operator.
		};
	}
}