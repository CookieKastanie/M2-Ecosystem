#include <Ecosystem/simulation/Terrain.hpp>
#include <Ecosystem/utils/Random.hpp>
#include <iostream>
#include "Ecosystem/entities/Bunny.hpp"
#include "Ecosystem/entities/Fox.hpp"

Terrain::Terrain(unsigned int size,
				 CreationProbabilities *probs,
				 Animal::Rules *bunnyRules,
				 Animal::Rules *foxRules,
				 Vegetal::Rules *plantRules)
	: size{size}, neighbors{4}, state{0},
	probs{probs}, bunnyRules{bunnyRules}, foxRules{foxRules}, plantRules{plantRules} {

}

Terrain::~Terrain() {
	for(Cell &cell : cells) {
		cell.deleteAnimal();
		cell.deleteVegetal();
	}
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

			bool bunnySpawn = Random::greaterThan(1. - probs->bunny);
			bool foxSpawn = Random::greaterThan(1. - probs->fox);

			// choisir entre bunny et fox (1 chance / 2)
			if(bunnySpawn && foxSpawn) {
				bunnySpawn = Random::greaterThan(.5);
				if(bunnySpawn) foxSpawn = false;
			}

			if(bunnySpawn) cell.animal = new Bunny{bunnyRules};
			if(foxSpawn) cell.animal = new Fox{foxRules};
			
			if(cell.haveAnimal()) {
				cell.animal->getGraphicTransform().setPosition(x, 0, y);
				cell.animal->getGraphicTransform().savePrevious();
			}

			if(Random::greaterThan(1. - probs->plant)) {
				cell.vegetal = new Vegetal{plantRules};
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
	for(Cell &cell : cells) {
		int x = cell.x;
		int y = cell.y;
			
		neighbors.clear();
		if(x > 0)        neighbors.push_back(&at(x - 1, y));
		if(x < size - 1) neighbors.push_back(&at(x + 1, y));
		if(y > 0)        neighbors.push_back(&at(x, y - 1));
		if(y < size - 1) neighbors.push_back(&at(x, y + 1));

		if(cell.haveAnimal() && cell.animal->getState() != state) {
			if(cell.animal->isDead()) {
				cell.deleteAnimal();
			} else {
				cell.animal->setState(state);
				cell.animal->update(&cell, neighbors);
			}
		}

		if(cell.haveVegetal() && cell.vegetal->getState() != state) {
			if(cell.vegetal->isDead()) {
				cell.deleteVegetal();
			} else {
				cell.vegetal->setState(state);
				cell.vegetal->update(&cell, neighbors);
			}
		}
	}

	state = state == 0 ? 1 : 0;
}

int Terrain::getSize() {
	return size;
}

std::vector<Cell> &Terrain::getCells() {
	return cells;
}

std::ostream &operator<<(std::ostream &os, Terrain &terrain) {
	for(int y = 0; y < terrain.size; ++y) {
		for(int x = 0; x < terrain.size; ++x) {
			Cell &cell = terrain.at(x, y);
			os << cell;
		}

		os << std::endl;
	}

	return os;
}
