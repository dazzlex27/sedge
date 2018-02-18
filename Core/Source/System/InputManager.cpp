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
#include "MemoryManagement.h"

using namespace s3dge;

static const float _elapsedDoubleClickThreshold = 0.5f;

InputManager::InputManager()
{
	_keysDown = new bool[KEYS_COUNT];
	memset(_keysDown, 0, sizeof(bool) * KEYS_COUNT);
	_keysClicked = new bool[KEYS_COUNT];
	memset(_keysClicked, 0, sizeof(bool) * KEYS_COUNT);
	_keysDoubleClicked = new bool[KEYS_COUNT];
	memset(_keysDoubleClicked, 0, sizeof(bool) * KEYS_COUNT);
	_doubleClickTimers = new Timer[KEYS_COUNT];
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