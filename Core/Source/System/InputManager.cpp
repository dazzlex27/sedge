/*
===========================================================================
InputManager.cpp

Implements InputManager class.
===========================================================================
*/

#include "InputManager.h"
#include "Platform/KeyCodes.h"
#include <string.h>
#include "Timer.h"
#include "Log.h"
#include "DeleteMacros.h"

using namespace s3dge;

static float _elapsedDoubleClickThreshold = 0.5f;

Point2D InputManager::_mousePosition;
Vector2 InputManager::_mouseDisplacement;
bool* InputManager::_keysDown;
bool* InputManager::_keysClicked;
bool* InputManager::_keysDoubleClicked;
bool InputManager::_initialized;
Timer* InputManager::_doubleClickTimers;

void InputManager::Initialize()
{
	if (!_initialized)
	{
		_keysDown = new bool[KEYS_COUNT];
		memset(_keysDown, 0, sizeof(bool) * KEYS_COUNT);
		_keysClicked = new bool[KEYS_COUNT];
		memset(_keysClicked, 0, sizeof(bool) * KEYS_COUNT);
		_keysDoubleClicked = new bool[KEYS_COUNT];
		memset(_keysDoubleClicked, 0, sizeof(bool) * KEYS_COUNT);
		_doubleClickTimers = new Timer[KEYS_COUNT];

		_initialized = true;
	}
	else
	{
		LOG_WARNING("Input manager has already been initialized");
	}
}

void InputManager::Update()
{
	_mouseDisplacement.x = 0.0f;
	_mouseDisplacement.y = 0.0f;

	_keysDown[S3_KEY_MWUP] = false;
	_keysDown[S3_KEY_MWDOWN] = false;

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

void InputManager::Dispose()
{
	if (_initialized)
	{
		SafeDeleteArray(_keysDown);
		SafeDeleteArray(_keysClicked); 
		SafeDeleteArray(_keysDoubleClicked);
		SafeDeleteArray(_doubleClickTimers);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the input manager as it was not initialized!");
	}
}