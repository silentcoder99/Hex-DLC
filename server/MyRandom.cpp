#include "MyRandom.h"
#include <random>
#include <chrono>

MyRandom::MyRandom() {
}

double MyRandom::real(double min, double max) {
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

int MyRandom::integer(int max) {
	return (int)real(0, max);
}