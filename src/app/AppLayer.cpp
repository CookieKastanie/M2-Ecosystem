#include "Ecosystem/app/AppLayer.hpp"
#include <imgui/imgui.h>

using namespace Akila;

AppLayer::AppLayer(): terrain{30}, play{true} {
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
	if(play) {
		terrain.update();
		//terrain.print();
	}
}

void AppLayer::draw() {
	camera->update();

	Core::renderer->useDefaultFrameBuffer();
	Core::renderer->clear();

	auto shader = Core::resourcePool->getShader("simple");
	auto bunnyMat = Core::resourcePool->getMaterial("bunny");
	auto bunnyMesh = Core::resourcePool->getMesh("bunny");
	auto foxMat = Core::resourcePool->getMaterial("fox");
	auto foxMesh = Core::resourcePool->getMesh("fox");

	auto plantMat = Core::resourcePool->getMaterial("plant");
	auto plantMesh = Core::resourcePool->getMesh("plant");
	auto groundMesh = Core::resourcePool->getMesh("ground");

	Transform transform;
	terrain.foreach([&transform, &shader,
					&bunnyMat, &bunnyMesh,
					&foxMat, &foxMesh,
					&plantMat, &plantMesh, &groundMesh](Cell *cell, int x, int y) {

		transform.setPosition((float)x, 0, (float)y);
		shader->send("M", transform.toMatrix());

		if(cell->haveAnimal()) {
			switch(cell->animal->getSpecie()) {
				case Animal::Species::BUNNY:
					Core::renderer->render(bunnyMat.get(), bunnyMesh.get());
					break;
				case Animal::Species::FOX:
					Core::renderer->render(foxMat.get(), foxMesh.get());
					break;
			}
		}

		if(cell->haveVegetal()) {
			Core::renderer->render(plantMat.get(), plantMesh.get());
		}

		Core::renderer->render(plantMat.get(), groundMesh.get());
	});
}

void imGuiAnimalRules(Animal::Rules &rules, int id) {
	ImGui::PushID(id);

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

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::SliderInt("reproduicngEnergyCost", &rules.reproduicngEnergyCost, 0, 100);
	ImGui::SliderInt("marginReproductionEnergy", &rules.marginReproductionEnergy, 0, 100);
	ImGui::DragIntRange2(
		"reproductionCDRange",
		&rules.reproductionCDRange[0], &rules.reproductionCDRange[1],
		1, 1, 100, "Min: %.0f", "Max: %.0f"
	);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::SliderInt("movingEnergyCost", &rules.movingEnergyCost, 0, 10);
	ImGui::SliderInt("eatingEnergyGain", &rules.eatingEnergyGain, 0, 100);
	ImGui::SliderInt("maxEnergy", &rules.maxEnergy, 0, 200);

	ImGui::PopID();
}

void imGuiVegetalRules(Vegetal::Rules &rules, int id) {
	ImGui::PushID(id);

	ImGui::DragIntRange2(
		"initialTTLRange",
		&rules.initialTTLRange[0], &rules.initialTTLRange[1],
		1, 1, 500, "Min: %.0f", "Max: %.0f"
	);

	ImGui::DragIntRange2(
		"spraySeedCDRange",
		&rules.spraySeedCDRange[0], &rules.spraySeedCDRange[1],
		1, 1, 100, "Min: %.0f", "Max: %.0f"
	);

	ImGui::PopID();
}

void AppLayer::drawImGui() {
	ImGui::Begin("Settings");

	if(ImGui::CollapsingHeader("Simulation")) {
		ImGui::SliderFloat("Delta", &Time::fixedDelta, 0.01, 1.);

		if(play) {
			if(ImGui::Button("Pause")) play = false;
		} else {
			if(ImGui::Button("Play")) play = true;
		}
	}

	if(ImGui::CollapsingHeader("Terrain creation probabilities")) {
		Terrain::CreationProbabilities &probs = terrain.getCreationProbs();
		ImGui::SliderFloat("Bunny", &probs.bunny, 0, 1);
		ImGui::SliderFloat("Fox", &probs.fox, 0, 1);
		ImGui::SliderFloat("Plant", &probs.plant, 0, 1);
		if(ImGui::Button("Default values")) terrain.setDefaultCreationProbs();
		if(ImGui::Button("Reset terrain")) terrain.reset();
	}

	ImGui::End();

	///////////////////////////////////////////////////////////////////////////

	ImGui::Begin("Rules");
	if(ImGui::CollapsingHeader("Bunnies")) {
		imGuiAnimalRules(terrain.getBunnyRules(), 0);
		if(ImGui::Button("Default settings###0")) terrain.setDefaultBunnyRules();
	}

	if(ImGui::CollapsingHeader("Foxes")) {
		imGuiAnimalRules(terrain.getFoxRules(), 1);
		if(ImGui::Button("Default settings###1")) terrain.setDefaultFoxRules();
	}

	if(ImGui::CollapsingHeader("Plant")) {
		imGuiVegetalRules(terrain.getPlantRules(), 2);
		if(ImGui::Button("Default settings###2")) terrain.setDefaultPlantRules();
	}
	ImGui::End();
}
