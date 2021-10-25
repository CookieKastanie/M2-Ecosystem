#include <Ecosystem/Animal.hpp>
#include "Ecosystem/Random.hpp"

Animal::Animal(): specie{ Species::MICE }, carnivorous{ false } {
	reproductionRT = Random::rangeInt(5, 20);
	starvingRT = Random::rangeInt(10, 30);
}

void Animal::update(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	int done = true;

	done = tryEat(currentCell);
	if(!done && canReproduce()) done = tryReproduce(neighbords);
	if(!done) done = randomMove(currentCell, neighbords);

	--starvingRT;
	--reproductionRT;
	if(starvingRT <= 0) die();
}

bool Animal::randomMove(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	int index = Random::rangeInt(0, neighbords.size() - 1);
	Cell *cell = neighbords[index];
	if(cell->animal == nullptr) {
		currentCell->animal = nullptr;
		cell->animal = this;

		return true;
	}

	return false;
}

bool Animal::canReproduce() {
	return starvingRT > 15 && reproductionRT <= 0;
}

bool Animal::tryReproduce(std::vector<Cell *> const &neighbords) {
	Animal *mate = nullptr;
	Cell *empty = nullptr;

	for(Cell *cell : neighbords) {
		if(mate == nullptr && cell->animal != nullptr) {
			if(cell->animal->canReproduce()) mate = cell->animal;
		} else if(empty == nullptr && cell->animal == nullptr) {
			empty = cell;
		}
	}

	if(mate != nullptr && empty != nullptr) {
		empty->animal = new Animal{};

		reproductionRT += Random::rangeInt(15, 30);
		mate->reproductionRT += Random::rangeInt(15, 30);

		starvingRT -= 10;
		mate->starvingRT -= 10;

		return true;
	}

	return false;
}

bool Animal::tryEat(Cell *currentCell) {
	if(starvingRT < 20 && currentCell->vegetal != nullptr) {
		starvingRT += 10;
		delete currentCell->vegetal;
		currentCell->vegetal = nullptr;

		return true;
	}

	return false;
}


std::ostream &operator<<(std::ostream &os, Animal const &a) {
	switch(a.specie) {
		case Animal::Species::MICE:
			os << "M";
			break;

		case Animal::Species::FOX:
			os << "F";
			break;
	}
	
	return os;
}