/*
===========================================================================
InputManager.cpp

Implements InputManager class.
===========================================================================
*/

#include "InputManager.h"
#include <string.h>
#include "Stopwatch.h"
#include "Logger.h"
#include "MemoryManagement.h"
#include <GLFW/glfw3.h>

using namespace sedge;

static const float _elapsedDoubleClickThreshold = 0.5f;

InputManager::InputManager()
{
	_keysDown = new bool[KEYS_COUNT];
	memset(_keysDown, 0, sizeof(bool) * KEYS_COUNT);
	_keysClicked = new bool[KEYS_COUNT];
	memset(_keysClicked, 0, sizeof(bool) * KEYS_COUNT);
	_keysDoubleClicked = new bool[KEYS_COUNT];
	memset(_keysDoubleClicked, 0, sizeof(bool) * KEYS_COUNT);
	_doubleClickTimers = new Stopwatch[KEYS_COUNT];
}

InputManager::~InputManager()
{
	SafeDeleteArray(_keysDown);
	SafeDeleteArray(_keysClicked);
	SafeDeleteArray(_keysDoubleClicked);
	SafeDeleteArray(_doubleClickTimers);
}

void InputManager::Update()
{
	_mouseDisplacement.x = 0.0f;
	_mouseDisplacement.y = 0.0f;

	// TODO: add mouse wheel input for FOV change
	// _keysDown[GLFW_KEY_MWUP] = false;
	// _keysDown[GLFW_KEY_MWDOWN] = false;

	memset(_keysDoubleClicked, 0, sizeof(bool) * KEYS_COUNT);

	for (int i = 0; i < KEYS_COUNT; i++)
	{
		if (_doubleClickTimers[i].IsRunning())
		{
			if (_doubleClickTimers[i].ElapsedS() > _elapsedDoubleClickThreshold)
			{
				_doubleClickTimers[i].Stop();
				continue;
			}

			if (_keysClicked[i])
				_keysDoubleClicked[i] = true;
		}

		if (_keysClicked[i])
			_doubleClickTimers[i].Start();
	}

	memset(_keysClicked, 0, sizeof(bool) * KEYS_COUNT);
}

void InputManager::UpdateCursorPosition(double xPos, double yPos)
{
	_mousePosition.x = xPos;
	_mousePosition.y = yPos;
}

void InputManager::UpdateCursorDisplacement(double xValue, double yValue)
{
	_mouseDisplacement.x = xValue;
	_mouseDisplacement.y = yValue;
}

void InputManager::UpdateKeyState(uint key, bool pressed)
{
	_keysDown[key] = pressed;
	_keysClicked[key] = pressed;
}
