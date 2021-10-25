#include <Ecosystem/Random.hpp>
#include <random>
#include <ctime>

void Random::init() {
	std::srand(std::time(nullptr));
}

float Random::generate() {
	return (float)std::rand() / (float)RAND_MAX;
}

bool Random::greaterThan(float value) {
	return value < generate();
}

int Random::rangeInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}
