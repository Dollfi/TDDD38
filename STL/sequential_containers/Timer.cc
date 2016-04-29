#include "Timer.h"
#include <chrono>
#include <iostream>
using namespace std::chrono;
Timer::Timer()
{
	tick();
}
Timer::Timer(std::ostream & output)
	: os{ &output }
{
	tick();
}

Timer::~Timer()
{
	if (os)
	{
		*os << "Alive for " << tock().count() << " us";
	}
}
void Timer::tick()
{
	start = high_resolution_clock::now();
}
microseconds Timer::tock() const
{
	return duration_cast<microseconds>(high_resolution_clock::now() - start);
}

