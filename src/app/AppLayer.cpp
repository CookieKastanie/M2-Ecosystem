#include "Ecosystem/app/AppLayer.hpp"

using namespace Akila;

AppLayer::AppLayer(): terrain{20} {
	Core::resourcePool->loadResourceFile("main.res", []() -> void {

	});

	camera = std::make_shared<MouseCamera>(Core::display->getMouse());
	Core::renderer->setSharedCamera(camera);
	Core::renderer->setClearColor(0.5, 0.6, 1.0);
	Core::renderer->disable(Renderer::Capability::CULL_FACE);

	float s = (float)terrain.getSize() / 2. - 0.5;
	camera->setCenter({s, 0, s});

	Core::display->getKeybord()->onKeyPress([this](Keyboard::Key key) {
		if(key == Keyboard::Key::SPACE) {
			terrain.reset();
		}
	});
}

void AppLayer::update() {
	terrain.update();
	//terrain.print();
}

void AppLayer::draw() {
	camera->update();

	Core::renderer->useDefaultFrameBuffer();
	Core::renderer->clear();

	auto shader = Core::resourcePool->getShader("simple");
	auto miceMat = Core::resourcePool->getMaterial("mice");
	auto miceMesh = Core::resourcePool->getMesh("mice");

	auto plantMat = Core::resourcePool->getMaterial("plant");
	auto plantMesh = Core::resourcePool->getMesh("plant");
	auto groundMesh = Core::resourcePool->getMesh("ground");

	Transform transform;
	terrain.foreach([&transform, &shader, &miceMat, &miceMesh, &plantMat, &plantMesh, &groundMesh](Cell *cell, int x, int y) {
		transform.setPosition((float)x, 0, (float)y);
		shader->send("M", transform.toMatrix());

		if(cell->haveAnimal()) {
			Core::renderer->render(miceMat.get(), miceMesh.get());
		}

		if(cell->haveVegetal()) {
			Core::renderer->render(plantMat.get(), plantMesh.get());
		}

		Core::renderer->render(plantMat.get(), groundMesh.get());
	});
}
