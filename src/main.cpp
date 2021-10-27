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
#include <Akila/entities/Transform.hpp>

#include <iostream>
#include <Ecosystem/Random.hpp>
#include <Ecosystem/Terrain.hpp>

#include <Ecosystem/MouseCamera.hpp>

class TestLayer: public Akila::Layer {
private:
	Terrain terrain;
	std::shared_ptr<MouseCamera> camera;

public:
	TestLayer(): terrain{20} {
		Akila::Core::resourcePool->loadResourceFile("main.res", []() -> void {

		});

		camera = std::make_shared<MouseCamera>(Akila::Core::display->getMouse());
		Akila::Core::renderer->setSharedCamera(camera);
		Akila::Core::renderer->setClearColor(0.5, 0.5, 0.8);
		Akila::Core::renderer->disable(Akila::Renderer::Capability::CULL_FACE);
	}

	void update() override {
		terrain.update();
		//terrain.print();
	}

	void draw() override {
		camera->update();

		Akila::Core::renderer->useDefaultFrameBuffer();
		Akila::Core::renderer->clear();

		auto shader = Akila::Core::resourcePool->getShader("simple");
		auto miceMat = Akila::Core::resourcePool->getMaterial("mice");
		auto miceMesh = Akila::Core::resourcePool->getMesh("mice");

		auto plantMat = Akila::Core::resourcePool->getMaterial("plant");
		auto plantMesh = Akila::Core::resourcePool->getMesh("plant");
		auto groundMesh = Akila::Core::resourcePool->getMesh("ground");

		Akila::Transform transform;
		terrain.foreach([&transform, &shader, &miceMat, &miceMesh, &plantMat, &plantMesh, &groundMesh](Cell *cell, int x, int y) {
			transform.setPosition((float)x, 0, (float)y);
			shader->send("M", transform.toMatrix());
			
			if(cell->haveAnimal()) {
				Akila::Core::renderer->render(miceMat.get(), miceMesh.get());
			}

			if(cell->haveVegetal()) {
				Akila::Core::renderer->render(plantMat.get(), plantMesh.get());
			}

			Akila::Core::renderer->render(plantMat.get(), groundMesh.get());
		});
	}
};


int main(int argc, char *argv[]) {
	Random::init();

	return Akila::Core::run(argc, argv, [](void) {
		Akila::Time::fixedDelta = 0.2;
		Akila::FileSystem::setResourceFolder("resources");

		Akila::Core::layerManager->add(new TestLayer{});
	});
}
