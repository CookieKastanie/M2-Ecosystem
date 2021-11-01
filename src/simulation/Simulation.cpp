#include <Ecosystem/simulation/Simulation.hpp>

Simulation::Simulation(): terrain{20, &probs, &bunnyRules, &foxRules, &plantRules}, playing{true} {
	setDefaultCreationProbs();
	setDefaultBunnyRules();
	setDefaultFoxRules();
	setDefaultPlantRules();

	terrain.reset();
}

void Simulation::update() {
	if(playing) {
		terrain.update();

		/*/
		std::cout << "-----------" << std::endl;
		std::cout << terrain << std::endl;
		//*/
	}
}

void Simulation::play() {
	playing = true;
}

void Simulation::pause() {
	playing = false;
}

bool Simulation::isPlaying() {
	return playing;
}

void Simulation::setDefaultCreationProbs() {
	probs.bunny = 0.25;
	probs.fox = 0.03;
	probs.plant = 0.6;
}

Terrain::CreationProbabilities &Simulation::getCreationProbs() {
	return probs;
}

void Simulation::setDefaultBunnyRules() {
	bunnyRules.initialEnergyRange[0] = 45;
	bunnyRules.initialEnergyRange[1] = 50;

	bunnyRules.initialTTLRange[0] = 100;
	bunnyRules.initialTTLRange[1] = 150;

	bunnyRules.marginReproductionEnergy = 20;
	bunnyRules.maxEnergy = 50;
	bunnyRules.movingEnergyCost = 1;
	bunnyRules.reproduicngEnergyCost = 30;
	bunnyRules.eatingEnergyGain = 40;

	bunnyRules.reproductionCDRange[0] = 40;
	bunnyRules.reproductionCDRange[1] = 50;
}

void Simulation::setDefaultFoxRules() {
	foxRules.initialEnergyRange[0] = 40;
	foxRules.initialEnergyRange[1] = 60;

	foxRules.initialTTLRange[0] = 350;
	foxRules.initialTTLRange[1] = 450;

	foxRules.marginReproductionEnergy = 30;
	foxRules.maxEnergy = 150;
	foxRules.movingEnergyCost = 0;
	foxRules.reproduicngEnergyCost = 40;
	foxRules.eatingEnergyGain = 30;

	foxRules.reproductionCDRange[0] = 100;
	foxRules.reproductionCDRange[1] = 150;
}

void Simulation::setDefaultPlantRules() {
	plantRules.initialTTLRange[0] = 50;
	plantRules.initialTTLRange[1] = 100;

	plantRules.spraySeedCDRange[0] = 10;
	plantRules.spraySeedCDRange[1] = 20;
}

Animal::Rules &Simulation::getBunnyRules() {
	return bunnyRules;
}

Animal::Rules &Simulation::getFoxRules() {
	return foxRules;
}

Vegetal::Rules &Simulation::getPlantRules() {
	return plantRules;
}

Terrain &Simulation::getTerrain() {
	return terrain;
}
