// a simple class to keep track of time.
#pragma once
#include <chrono>
// only declarations from the iostream header (smaller size, good for headers)
#include <iosfwd>
class Timer
{
public:
    // will print total lifetime of the object if initialized with a stream
	Timer();
	explicit Timer(std::ostream & output);
	~Timer();

    // resets the internal time_point
	void tick();
    // returns time taken from last reset
	std::chrono::microseconds tock() const;

private:
	std::ostream * os{};
    // the clock with the smallest tick length
	std::chrono::high_resolution_clock::time_point start;
};
