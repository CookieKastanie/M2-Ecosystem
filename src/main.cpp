#include <iostream>
#include <Ecosystem/Random.hpp>
#include <Ecosystem/Terrain.hpp>

#include <chrono>
#include <thread>

int main() {
	Random::init();

	Terrain terrain{ 10 };

	for(;;) {
		terrain.update();
		terrain.print();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
