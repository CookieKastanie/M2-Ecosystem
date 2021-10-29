#include "Ecosystem/app/AppLayer.hpp"
#include <imgui/imgui.h>

using namespace Akila;

AppLayer::AppLayer(): terrain{30} {
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

void imGuiAnimalRules(Animal::Rules &rules) {
	ImGui::BeginGroup();
		ImGui::DragIntRange2(
			"initialTTLRange",
			&rules.initialTTLRange[0], &rules.initialTTLRange[1],
			1, 1, 500, "Min: %.0f", "Max: %.0f"
		);

		ImGui::DragIntRange2(
			"initialEnergyRange",
			&rules.initialEnergyRange[0], &rules.initialEnergyRange[1],
			1, 1, 100, "Min: %.0f", "Max: %.0f"
		);
	ImGui::EndGroup();

	ImGui::BeginGroup();
		ImGui::SliderInt("reproduicngEnergyCost", &rules.reproduicngEnergyCost, 0, 100);
		ImGui::SliderInt("marginReproductionEnergy", &rules.marginReproductionEnergy, 0, 100);
		ImGui::DragIntRange2(
			"reproductionCDRange",
			&rules.reproductionCDRange[0], &rules.reproductionCDRange[1],
			1, 1, 100, "Min: %.0f", "Max: %.0f"
		);
	ImGui::EndGroup();
	
	ImGui::BeginGroup();
		ImGui::SliderInt("movingEnergyCost", &rules.movingEnergyCost, 0, 10);
		ImGui::SliderInt("eatingEnergyGain", &rules.eatingEnergyGain, 0, 100);
		ImGui::SliderInt("maxEnergy", &rules.maxEnergy, 0, 100);
	ImGui::EndGroup();
}

void AppLayer::drawImGui() {
	ImGui::Begin("Settings");
	ImGui::SliderFloat("Sim delta", &Time::fixedDelta, 0.01, 1.);
	if(ImGui::Button("Reset")) terrain.reset();
	ImGui::End();

	Animal::Rules &bunnyRules = terrain.getBunnyRules();
	ImGui::Begin("Bunnies rules");
	imGuiAnimalRules(bunnyRules);
	ImGui::End();
}
