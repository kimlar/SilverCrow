#pragma once

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

// Usage:
//		#include "Timer.h"
//		Timer time;
//		timer.Start();
//		...
//		time.Stop();
//		time.Print();
//		double dt = time.GetDuration();
// Output:
//		Duration: 0.00328027 seconds.

class Timer
{
public:
	// Measuring time
	void Start() { t0 = std::chrono::steady_clock::now(); }
	void Stop() { t1 = std::chrono::steady_clock::now(); CalculateDuration(); }
	double GetDuration() { return time_span.count(); } // in seconds

	// Utils
	void Print() { std::cout << "Duration: " << time_span.count() << " seconds." << std::endl; }
private:
	// Internals
	void CalculateDuration() { time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0); }

	std::chrono::steady_clock::time_point t0;
	std::chrono::steady_clock::time_point t1;
	std::chrono::duration<double> time_span;
};
