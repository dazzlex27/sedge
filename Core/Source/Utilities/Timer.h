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

		std::chrono::time_point<clock> m_Start;

	public:
		Timer()
		{
			Start();
		}

		void Start()
		{
			m_Start = clock::now();
		}

		float ElapsedS()
		{
			return std::chrono::duration_cast<ms>(clock::now() - m_Start).count() / 1000;
		}

		float ElapsedNS()
		{
			return std::chrono::duration_cast<ns>(clock::now() - m_Start).count();
		}

		float ElapsedMS()
		{
			return std::chrono::duration_cast<ms>(clock::now() - m_Start).count();
		}
	};
}