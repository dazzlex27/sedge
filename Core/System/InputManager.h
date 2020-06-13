/*
===========================================================================
InputManager.h

Handles all user input.
===========================================================================
*/

#pragma once

#include <map>
#include <CustomTypes.h>
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace sedge
{
	class Stopwatch;

#define KEYS_COUNT 10240

	class InputManager
	{
	private:
		Vector2 _mousePosition; // x = [0, windowWidth]; y = [0, windowHeight]
		Vector2 _mouseDisplacement; // x = [ -1, 1]; y = [-1, 1], default - 0,0
		bool* _keysDown;
		bool* _keysClicked;
		bool* _keysDoubleClicked;
		Stopwatch* _doubleClickTimers;

	public:
		void Update();
		inline const Vector2& GetMousePosition() const { return _mousePosition; }
		inline const Vector2& GetMouseDisplacement() const { return _mouseDisplacement; }

		void UpdateCursorPosition(double xPos, double yPos);
		void UpdateKeyState(uint key, bool pressed);

		inline const bool KeyDown(uint key) const { return _keysDown[key]; }
		inline const bool KeyClicked(uint key) const { return _keysClicked[key]; }
		inline const bool KeyDoubleClicked(uint key) const { return _keysDoubleClicked[key]; }

		InputManager();
		~InputManager();
	};
}