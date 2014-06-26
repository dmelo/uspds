#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <time.h>
#include <stdlib.h>

#include <sys/time.h>

class Random {
	private:
		unsigned int seed;

	public:
		Random();
		Random(int seed);

		long int nextLongInt();
		long int nextLongInt(long int value);
		double nextDouble(); // [0,1]
		double nextDouble(long int max); // [0,max]
		double nextDouble(double max); // [0,max]
		char nextChar();
		char* nextString(int size);
};

#endif
