/*
===========================================================================
InputManager.h

Handles all user input.
===========================================================================
*/

#pragma once

#define KEYS_COUNT 256

#include <vector>
#include "CustomTypes.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace s3dge
{
	class Window;
	class Stopwatch;

	class InputManager
	{
	private:
		Vector3 _mousePosition; // x = [0, windowWidth]; y = [0, windowHeight]
		Vector2 _mouseDisplacement; // x = [ -1, 1]; y = [-1, 1], default - 0,0
		bool* _keysDown;
		bool* _keysClicked;
		bool* _keysDoubleClicked;
		Stopwatch* _doubleClickTimers;

	public:
		void Update();
		inline const Vector3& GetMousePosition() const { return _mousePosition; }
		inline const Vector2& GetMouseDisplacement() const { return _mouseDisplacement; }
		inline const bool KeyDown(uint key) const { return _keysDown[key]; }
		inline const bool KeyClicked(uint key) const { return _keysClicked[key]; }
		inline const bool KeyDoubleClicked(uint key) const { return _keysDoubleClicked[key]; }

		friend void key_callback(const Window*const window, const int key, const int command);
		friend void cursor_position_callback(Window*const window);
		
		~InputManager();

	private:
		InputManager();
		InputManager(const InputManager& tRef) = delete;
		InputManager& operator = (const InputManager& tRef) = delete;

		friend class Window;
	};
}