#include "MyRandom.h"
#include <random>
#include <chrono>

MyRandom::MyRandom() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	m_generator.seed(seed);
}

double MyRandom::real() {
	std::uniform_real_distribution<double> distribution(-1, 1);
	return distribution(m_generator);
}

int MyRandom::integer(int max) {
	std::uniform_int_distribution<int> distribution(0, max - 1);
	return distribution(m_generator);
}