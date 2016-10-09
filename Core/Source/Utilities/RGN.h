#pragma once

#include <random>

namespace s3dge
{
	class RNG
	{
	private:
		std::random_device rng;
		std::mt19937 gen;
		std::uniform_real_distribution<> dis;

	public:
		RNG()
		{
			std::mt19937 gen(rng());
			dis = std::uniform_real_distribution<>(0, 1);
		}

		RNG(int boundA, int boundB)
		{
			std::mt19937 gen(rng());
			dis = std::uniform_real_distribution<>(boundA, boundB);
		}

		~RNG() { }
		
		inline double Next() { return dis(gen);	}

	private:
		RNG(const RNG& tRef) = delete;				// Disable copy constructor.
		RNG& operator = (const RNG& tRef) = delete;	// Disable assignment operator.
	};
}