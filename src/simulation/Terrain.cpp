#include <Ecosystem/simulation/Terrain.hpp>
#include <Ecosystem/utils/Random.hpp>
#include <iostream>
#include "Ecosystem/entities/Bunny.hpp"

Terrain::Terrain(unsigned int size): size{size}, neighbords{4}, state{0} {
	bunnyRules.initialEnergyRange[0] = 10;
	bunnyRules.initialEnergyRange[1] = 30;

	bunnyRules.initialTTLRange[0] = 100;
	bunnyRules.initialTTLRange[1] = 200;

	bunnyRules.marginReproductionEnergy = 15;
	bunnyRules.maxEnergy = 50;
	bunnyRules.movingEnergyCost = 0;
	bunnyRules.reproduicngEnergyCost = 25;
	bunnyRules.eatingEnergyGain = 20;

	bunnyRules.reproductionCDRange[0] = 20;
	bunnyRules.reproductionCDRange[1] = 40;

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

			if(Random::greaterThan(0.6)) {
				if(Random::greaterThan(.5)) {
					if(Random::greaterThan(.5)) {
						cell.animal = new Bunny{&bunnyRules};
					} else {
						//cell.animal = new Fox{&animalsRules};
					}
				} else {
					cell.vegetal = new Vegetal{};
				}
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

Animal::Rules &Terrain::getBunnyRules() {
	return bunnyRules;
}

void Terrain::foreach(std::function<void(Cell *, int, int)> cb) {
	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			cb(&at(x, y), x, y);
		}
	}
}
