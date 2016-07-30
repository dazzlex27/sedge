#pragma once

#include <vector>
#include "..\..\S3DGETypes.h"
#include <GL\glew.h>
#include "Utilities/Log.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Window
		{
			#define MODE_FULLSCREEN 1
			#define MODE_WINDOWED 0

		private:
			const char* m_Title;
			uint m_Width;
			uint m_Height;
			bool m_IsClosed;
			bool m_FullScreen;
			bool m_VSync;

		public:
			Window(const char* title,  uint width, uint height, bool fullscreen = false, bool vsync = true);
			~Window();

			void Clear();
			void Update();

			void SetVSync(bool vsync);
			void SetFullScreen(bool fullscreen);

			inline const char* GetTitle() const { return m_Title; }
			inline uint GetWidth() const { return m_Width; }
			inline uint GetHeight() const { return m_Height; }
			inline bool IsClosed() const { return m_IsClosed; }
			inline bool IsVSync() const { return m_VSync; }
			inline bool IsFullScreen() const { return m_FullScreen; }

		private:
			bool InitializeWindow();
			void UpdateWindow();
		};
	}
}