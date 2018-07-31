#include "Application.h"

int main()
{
	s3dge::RNG rng;

	s3dge::Stopwatch sw;

	sw.Start();
	
	auto dt = s3dge::DateTime::GetCurrentTime();
	auto dts = dt.ToShortTimeString();

	sw.Stop();

	std::cout << dts << std::endl;
	std::cout << sw.ElapsedMS() << " ms" << std::endl;

	getchar();

	return 0;
}