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
	state = 0;

	cells.resize((std::size_t)size * size);

	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			Cell &cell = cells[(std::size_t)y * size + x];
			cell.deleteAnimal();
			cell.deleteVegetal();

			bool bunnySpawn = Random::greaterThan(1. - probs.bunny);
			bool foxSpawn = Random::greaterThan(1. - probs.fox);

			// choisir entre bunny et fox (1 chance / 2)
			if(bunnySpawn && foxSpawn) {
				bunnySpawn = Random::greaterThan(.5);
				if(bunnySpawn) foxSpawn = false;
			}

			if(bunnySpawn) cell.animal = new Bunny{&bunnyRules};

			if(foxSpawn) cell.animal = new Fox{&foxRules};

			if(Random::greaterThan(1. - probs.plant)) {
				cell.vegetal = new Vegetal{&plantRules};
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
	probs.bunny = 0.2;
	probs.fox = 0.01;
	probs.plant = 0.6;
}

void Terrain::setDefaultBunnyRules() {
	bunnyRules.initialEnergyRange[0] = 10;
	bunnyRules.initialEnergyRange[1] = 30;

	bunnyRules.initialTTLRange[0] = 100;
	bunnyRules.initialTTLRange[1] = 200;

	bunnyRules.marginReproductionEnergy = 15;
	bunnyRules.maxEnergy = 50;
	bunnyRules.movingEnergyCost = 0;
	bunnyRules.reproduicngEnergyCost = 20;
	bunnyRules.eatingEnergyGain = 20;

	bunnyRules.reproductionCDRange[0] = 20;
	bunnyRules.reproductionCDRange[1] = 40;
}

void Terrain::setDefaultFoxRules() {
	foxRules.initialEnergyRange[0] = 40;
	foxRules.initialEnergyRange[1] = 60;

	foxRules.initialTTLRange[0] = 300;
	foxRules.initialTTLRange[1] = 400;

	foxRules.marginReproductionEnergy = 30;
	foxRules.maxEnergy = 100;
	foxRules.movingEnergyCost = 1;
	foxRules.reproduicngEnergyCost = 50;
	foxRules.eatingEnergyGain = 35;

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
