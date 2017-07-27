/*
===========================================================================
InputManager.h

Handles all user input.
===========================================================================
*/

#pragma once

#define KEYS_COUNT 256

#define IsKeyDown(key) InputManager::KeyDown(key)
#define IsKeyClicked(key) InputManager::KeyClicked(key)
#define IsKeyDoubleClicked(button) InputManager::MouseButtonClicked(button)
#define GetMouseDelta() InputManager::GetMouseDisplacement()
#define GetMousePos() InputManager::GetMousePosition()

#include "CustomTypes.h"
#include "Math/Point2D.h"
#include <vector>

namespace s3dge
{
	class Window;
	class Timer;

	class InputManager
	{
	private:
		static Point2D _mousePosition; // x = [0, windowWidth]; y = [0, windowHeight]
		static Vector2 _mouseDisplacement; // x = [ -1, 1]; y = [-1, 1], default - 0,0
		static bool* _keysDown;
		static bool* _keysClicked;
		static bool* _keysDoubleClicked;
		static bool _initialized;
		static Timer* _doubleClickTimers;
		static bool _freeCursorActive;

	public:
		static void Initialize();
		static void Update();
		static void Dispose();
		inline static const Point2D& GetMousePosition() { return _mousePosition; }
		inline static const Vector2& GetMouseDisplacement() { return _mouseDisplacement; }
		inline static const bool KeyDown(uint key) { return _keysDown[key]; }
		inline static const bool KeyClicked(uint key) { return _keysClicked[key]; }
		inline static const bool KeyDoubleClicked(uint key) { return _keysDoubleClicked[key]; }

		friend void key_callback(const Window* window, int key, int command);
		friend void cursor_position_callback(const Window* window);

	private:
		InputManager();
		InputManager(const InputManager& tRef) = delete;
		InputManager& operator = (const InputManager& tRef) = delete;
		~InputManager(void) {}
	};
}