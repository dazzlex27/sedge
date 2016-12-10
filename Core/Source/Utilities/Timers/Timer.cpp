#include "Timer.h"
#include "Internal/Log.h"

namespace s3dge
{
	Timer::Timer()
	{
		_startTime = clock::now();
		_stopTime = clock::now();
		_running = false;
	}

	void Timer::Start()
	{
		_running = true;
		_startTime = clock::now();
	}

	void Timer::Stop()
	{
		_stopTime = clock::now();
		_running = false;
	}

	float Timer::ElapsedS() const
	{
		if (_running)
			return std::chrono::duration_cast<ms>(clock::now() - _startTime).count() / 1000;
		else
			return std::chrono::duration_cast<ms>(_stopTime - _startTime).count() / 1000;
	}

	float Timer::ElapsedNS() const
	{
		if (_running)
			return std::chrono::duration_cast<ns>(clock::now() - _startTime).count();
		else
			return std::chrono::duration_cast<ns>(_stopTime - _startTime).count();
	}

	float Timer::ElapsedMS() const
	{
		if (_running)
			return std::chrono::duration_cast<ms>(clock::now() - _startTime).count();
		else
			return std::chrono::duration_cast<ms>(_stopTime - _startTime).count();
	}
}