#include "Ecosystem/app/AppLayer.hpp"
#include <imgui/imgui.h>

using namespace Akila;

AppLayer::AppLayer(): uiTerrainSize{20} {
	Core::resourcePool->loadResourceFile("main.res"); // async loading

	camera = std::make_shared<MouseCamera>(Core::display->getMouse());
	Core::renderer->setSharedCamera(camera);
	Core::renderer->setClearColor(0.5, 0.6, 1.0);
	Core::renderer->disable(Renderer::Capability::CULL_FACE);

	setCamaraToMapCenter();

	Core::display->getKeybord()->onKeyPress([this](Keyboard::Key key) {
		if(key == Keyboard::Key::SPACE) {
			simulation.getTerrain().reset();
		}
	});

	Time::fixedDelta = 0.2;
}

void AppLayer::setCamaraToMapCenter() {
	float s = (float)simulation.getTerrain().getSize() / 2. - 0.5;
	camera->setCenter({s, 0, s});
}

void AppLayer::update() {
	simulation.update();
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

	if(!simulation.isPlaying()) Time::mix = 1.;
	for(Cell &cell : simulation.getTerrain().getCells()) {
		if(cell.haveAnimal()) {
			shader->send("M", cell.animal->getGraphicTransform().toMatrixMix(Time::mix));
			switch(cell.animal->getSpecie()) {
				case Animal::Species::BUNNY:
					Core::renderer->render(bunnyMat.get(), bunnyMesh.get());
					break;
				case Animal::Species::FOX:
					Core::renderer->render(foxMat.get(), foxMesh.get());
					break;
			}
		}

		if(cell.haveVegetal()) {
			shader->send("M", cell.vegetal->getGraphicTransform().toMatrixMix(Time::mix));
			Core::renderer->render(plantMat.get(), plantMesh.get());
		}

		// ground
		Transform transform;
		transform.setPosition(cell.x, 0, cell.y);
		shader->send("M", transform.toMatrix());
		Core::renderer->render(plantMat.get(), groundMesh.get());
	};
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
	/////////////////
	/// Settings window
	/////////////////
	ImGui::Begin("Settings");

	if(ImGui::CollapsingHeader("Simulation")) {
		ImGui::SliderFloat("Delta", &Time::fixedDelta, 0.01, 1.);

		if(simulation.isPlaying()) {
			if(ImGui::Button("Pause")) simulation.pause();
		} else {
			if(ImGui::Button("Play")) simulation.play();
		}
	}

	/////////////////

	if(ImGui::CollapsingHeader("Terrain creation")) {
		Terrain::CreationProbabilities &probs = simulation.getCreationProbs();
		ImGui::SliderFloat("Bunny probability", &probs.bunny, 0, 1);
		ImGui::SliderFloat("Fox probability", &probs.fox, 0, 1);
		ImGui::SliderFloat("Plant probability", &probs.plant, 0, 1);
		if(ImGui::Button("Default values")) simulation.setDefaultCreationProbs();

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::SliderInt("Terrain size", &uiTerrainSize, 5, 50);
		if(ImGui::Button("Reset terrain")) {
			bool sizeChanged = simulation.getTerrain().getSize() != uiTerrainSize;
			simulation.getTerrain().reset(uiTerrainSize);
			if(sizeChanged) setCamaraToMapCenter();
		}
	}

	ImGui::End();

	/////////////////
	/// Rules window
	/////////////////
	ImGui::Begin("Rules");
	if(ImGui::CollapsingHeader("Bunnies")) {
		imGuiAnimalRules(simulation.getBunnyRules(), 0);
		if(ImGui::Button("Default settings###0")) simulation.setDefaultBunnyRules();
	}

	if(ImGui::CollapsingHeader("Foxes")) {
		imGuiAnimalRules(simulation.getFoxRules(), 1);
		if(ImGui::Button("Default settings###1")) simulation.setDefaultFoxRules();
	}

	if(ImGui::CollapsingHeader("Plant")) {
		imGuiVegetalRules(simulation.getPlantRules(), 2);
		if(ImGui::Button("Default settings###2")) simulation.setDefaultPlantRules();
	}
	ImGui::End();
}
