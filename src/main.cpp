/*
#include <iostream>
#include <Ecosystem/Random.hpp>
#include <Ecosystem/Terrain.hpp>

#include <chrono>
#include <thread>

int main() {
	Random::init();

	Terrain terrain{ 20 };

	for(;;) {
		terrain.update();
		terrain.print();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
*/

#include <Akila/core/Core.hpp>
#include <iostream>
#include <Ecosystem/Random.hpp>
#include <Ecosystem/Terrain.hpp>



class TestLayer: public Akila::Layer {
private:
	Terrain terrain;

public:
	TestLayer(): terrain{20} {

	}

	void update() override {
		terrain.update();
		terrain.print();
	}
};


int main(int argc, char *argv[]) {
	Random::init();

	return Akila::Core::run(argc, argv, [](void) {
		Akila::Time::fixedDelta = 0.5;
		Akila::Core::layerManager->add(new TestLayer{});
	});
}
