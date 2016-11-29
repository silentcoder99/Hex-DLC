#include "MyRandom.h"
#include <random>
#include <chrono>

MyRandom::MyRandom() {
}

double MyRandom::real(double min, double max) {
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

int MyRandom::integer(int max) {
	int randomNumber = (int)real(0, max);
	return randomNumber == max ? randomNumber - 1 : randomNumber;
}