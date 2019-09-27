#pragma once

#include <ctime>
#include <cmath>

//
// Set the initial random seed with current time
//
inline void SetRandomSeed()
{
	srand((unsigned int)time(0));
}

//
// Returns an random int between INT_MIN and INT_MAX. Do not forget to set random seed first.
//
inline int GetRandomInt()
{
	// RAND_MAX = 32767
	unsigned char bytes[4];
	bytes[0] = rand() % 256;
	bytes[1] = rand() % 256;
	bytes[2] = rand() % 256;
	bytes[3] = rand() % 256;

	return int((unsigned char)(bytes[3]) << 24 | (unsigned char)(bytes[2]) << 16 | (unsigned char)(bytes[1]) << 8 | (unsigned char)(bytes[0]));
}
