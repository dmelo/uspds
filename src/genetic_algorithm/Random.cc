#include "Random.h"

///////////////////
// Conferir o cast  em next*****
///////////////////



Random::Random() {
	struct timeval tv;

	// generating a rand seed
	gettimeofday(&tv, NULL);

	this->seed = tv.tv_sec * 1000000 + tv.tv_usec;

	srand(this->seed);
}

Random::Random(int seed) {
	this->seed = seed;
	srand(this->seed);
}

long int Random::nextLongInt() {
	return rand();
}

long int Random::nextLongInt(long int value) {
	return rand() % value;
}

// [0,1]
double Random::nextDouble() {
	return (double) rand() / (double) RAND_MAX;
}

// [0,max]
double Random::nextDouble(double max) {
	return (double ) (rand() * max) / (double) RAND_MAX;
}

double Random::nextDouble(long int max) {
	return this->nextDouble((double) max);
}

char Random::nextChar() {
	int c = this->nextLongInt(52); // 52 is the number of alpha chars A-Z and a-z

	if (c < 26)
		return 65+c; // uppercase
	else
		return 97+(c-26); // lowercase
}

char *Random::nextString(int size) {
	char *str = new char[size];
	int i;

	for (i = 0; i < size; i++) {
		str[i] = this->nextChar();
	}

	return str;
}
