#pragma once

#include <chrono>

namespace s3dge
{
	class Timer
	{
	private:
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::duration<float, std::milli> ms;
		typedef std::chrono::duration<float, std::nano> ns;

		std::chrono::time_point<clock> _start;

	public:
		Timer()
		{
			Start();
		}

		void Start()
		{
			_start = clock::now();
		}

		float ElapsedS()
		{
			return std::chrono::duration_cast<ms>(clock::now() - _start).count() / 1000;
		}

		float ElapsedNS()
		{
			return std::chrono::duration_cast<ns>(clock::now() - _start).count();
		}

		float ElapsedMS()
		{
			return std::chrono::duration_cast<ms>(clock::now() - _start).count();
		}
	};
}