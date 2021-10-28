#include <Akila/core/Core.hpp>
#include "Ecosystem/app/AppLayer.hpp"

int main(int argc, char *argv[]) {
	Random::init();

	return Akila::Core::run(argc, argv, []() {
		Akila::Time::fixedDelta = 0.3;
		Akila::FileSystem::setResourceFolder("resources");
		Akila::Core::display->setTitle("Ecosystem woula nardine");
		Akila::Core::layerManager->add(new AppLayer{});
	});
}
