#include <Ecosystem/Random.hpp>
#include <random>
#include <ctime>

void Random::init() {
	std::srand(std::time(nullptr));
}

float Random::generate() {
	return (float)std::rand() / (float)RAND_MAX;
}
