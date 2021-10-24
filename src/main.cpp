#include <iostream>
#include <Ecosystem/Random.hpp>
#include <Ecosystem/Terrain.hpp>

int main() {
	Random::init();

	Terrain terrain{ 10 };

	terrain.print();

	return 0;
}
