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
		private:
			const char* m_Title;
			uint m_Width;
			uint m_Height;
			bool m_IsClosed;
			bool m_FullScreen;

		public:
			Window(const char* title,  uint width, uint height, bool fullscreen = false);
			~Window();

			void Clear();
			void Update();

			inline const char* GetTitle() const { return m_Title; }
			inline uint GetWidth() const { return m_Width; }
			inline uint GetHeight() const { return m_Height; }
			inline bool IsClosed() const { return m_IsClosed; }

		private:
			bool InitializeWindow();
			void UpdateWindow();
		};
	}
}