#include <Ecosystem/simulation/Terrain.hpp>
#include <Ecosystem/utils/Random.hpp>
#include <iostream>
#include "Ecosystem/entities/Bunny.hpp"
#include "Ecosystem/entities/Fox.hpp"

Terrain::Terrain(unsigned int size): size{size}, neighbords{4}, state{0} {
	setDefaultCreationProbs();
	setDefaultBunnyRules();
	setDefaultFoxRules();
	setDefaultPlantRules();
	reset();
}

void Terrain::reset() {
	reset(size);
}

void Terrain::reset(int newSize) {
	size = newSize;

	state = 0;

	for(Cell &cell : cells) {
		cell.deleteAnimal();
		cell.deleteVegetal();
	}

	cells.resize((std::size_t)size * size);

	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			Cell &cell = at(x, y);
			cell.x = x;
			cell.y = y;

			bool bunnySpawn = Random::greaterThan(1. - probs.bunny);
			bool foxSpawn = Random::greaterThan(1. - probs.fox);

			// choisir entre bunny et fox (1 chance / 2)
			if(bunnySpawn && foxSpawn) {
				bunnySpawn = Random::greaterThan(.5);
				if(bunnySpawn) foxSpawn = false;
			}

			if(bunnySpawn) cell.animal = new Bunny{&bunnyRules};
			if(foxSpawn) cell.animal = new Fox{&foxRules};
			
			if(cell.haveAnimal()) {
				cell.animal->getGraphicTransform().setPosition(x, 0, y);
				cell.animal->getGraphicTransform().savePrevious();
			}

			if(Random::greaterThan(1. - probs.plant)) {
				cell.vegetal = new Vegetal{&plantRules};
				cell.vegetal->getGraphicTransform().setPosition(x, 0, y);
				cell.vegetal->getGraphicTransform().savePrevious();
			}
		}
	}
}

Cell &Terrain::at(int x, int y) {
	return cells[(std::size_t)y * size + x];
}

void Terrain::update() {
	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			Cell &cell = at(x, y);
			
			neighbords.clear();
			if(x > 0)        neighbords.push_back(&at(x - 1, y));
			if(x < size - 1) neighbords.push_back(&at(x + 1, y));
			if(y > 0)        neighbords.push_back(&at(x, y - 1));
			if(y < size - 1) neighbords.push_back(&at(x, y + 1));

			if(cell.haveAnimal() && cell.animal->getState() != state) {
				if(cell.animal->isDead()) {
					cell.deleteAnimal();
				} else {
					cell.animal->setState(state);
					cell.animal->update(&cell, neighbords);
				}
			}

			if(cell.haveVegetal() && cell.vegetal->getState() != state) {
				if(cell.vegetal->isDead()) {
					cell.deleteVegetal();
				} else {
					cell.vegetal->setState(state);
					cell.vegetal->update(&cell, neighbords);
				}
			}
		}
	}

	state = state == 0 ? 1 : 0;
}

void Terrain::print() {
	std::cout << "-----------" << std::endl;

	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			Cell &cell = at(x, y);
			std::cout << cell;
		}

		std::cout << std::endl;
	}

	std::cout << std::flush;
}

int Terrain::getSize() {
	return size;
}

void Terrain::setDefaultCreationProbs() {
	probs.bunny = 0.25;
	probs.fox = 0.03;
	probs.plant = 0.6;
}

Terrain::CreationProbabilities &Terrain::getCreationProbs() {
	return probs;
}

void Terrain::setDefaultBunnyRules() {
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

void Terrain::setDefaultFoxRules() {
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

void Terrain::setDefaultPlantRules() {
	plantRules.initialTTLRange[0] = 50;
	plantRules.initialTTLRange[1] = 100;

	plantRules.spraySeedCDRange[0] = 10;
	plantRules.spraySeedCDRange[1] = 20;
}

Animal::Rules &Terrain::getBunnyRules() {
	return bunnyRules;
}

Animal::Rules &Terrain::getFoxRules() {
	return foxRules;
}

Vegetal::Rules &Terrain::getPlantRules() {
	return plantRules;
}

void Terrain::foreach(std::function<void(Cell *, int, int)> cb) {
	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			cb(&at(x, y), x, y);
		}
	}
}
