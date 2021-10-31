#include <Akila/core/Core.hpp>
#include "Ecosystem/app/AppLayer.hpp"

int main(int argc, char *argv[]) {
	Random::init();

	return Akila::Core::run(argc, argv, []() {
		Akila::Time::fixedDelta = 0.2;
		Akila::FileSystem::setResourceFolder("resources");
		Akila::Core::display->setTitle(u8"Ecosystem - J�r�my Andr�");
		Akila::Core::display->setSize(1280, 720);
		Akila::Core::layerManager->add(new AppLayer{});
	});
}
