/*
===========================================================================
Stopwatch.h

Relies on C++11 <chrono> features.
===========================================================================
*/

#pragma once

#include <chrono>

namespace s3dge
{
	class Stopwatch
	{
	private:
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::duration<float, std::milli> ms;
		typedef std::chrono::duration<float, std::nano> ns;

		std::chrono::time_point<clock> _startTime;
		std::chrono::time_point<clock> _stopTime;
		bool _running;

	public:
		Stopwatch();

		inline bool IsRunning() const { return _running; }
		
		void Start();
		void Stop();
		float ElapsedS() const;
		float ElapsedNS() const;
		float ElapsedMS() const;
	};
}