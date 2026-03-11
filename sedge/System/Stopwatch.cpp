/*
===========================================================================
Stopwatch.cpp

Implements stopwatch functions. Will most likely be abstracted to incorporate a few timer engines via #ifdef's
===========================================================================
*/

#include "Stopwatch.h"

using namespace sedge;

Stopwatch::Stopwatch()
{
	_startTime = clock::now();
	_stopTime = clock::now();
	_running = false;
}

void Stopwatch::Start()
{
	_running = true;
	_startTime = clock::now();
}

void Stopwatch::Stop()
{
	_stopTime = clock::now();
	_running = false;
}

float Stopwatch::ElapsedS() const
{
	if (_running)
		return std::chrono::duration_cast<ms>(clock::now() - _startTime).count() / 1000;
	else
		return std::chrono::duration_cast<ms>(_stopTime - _startTime).count() / 1000;
}

float Stopwatch::ElapsedNS() const
{
	if (_running)
		return std::chrono::duration_cast<ns>(clock::now() - _startTime).count();
	else
		return std::chrono::duration_cast<ns>(_stopTime - _startTime).count();
}

float Stopwatch::ElapsedMS() const
{
	if (_running)
		return std::chrono::duration_cast<ms>(clock::now() - _startTime).count();
	else
		return std::chrono::duration_cast<ms>(_stopTime - _startTime).count();
}