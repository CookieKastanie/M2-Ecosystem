#include <Ecosystem/entities/Animal.hpp>
#include "Ecosystem/utils/Random.hpp"
#include "Ecosystem/entities/Vegetal.hpp"

Animal::Animal(Species specie, Rules *rules): specie{ specie }, rules{ rules } {
	ttl = Random::rangeInt(rules->initialTTLRange);
	energy = Random::rangeInt(rules->initialEnergyRange);
	reproductionCD = Random::rangeInt(rules->reproductionCDRange);
}

Animal::~Animal() {

}

Animal::Species Animal::getSpecie() {
	return specie;
}

void Animal::update(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	onUpdate(currentCell, neighbords);

	--ttl;
	--reproductionCD;
	--energy;
	if(energy <= 0 || ttl <= 0) die();
}

bool Animal::move(Cell *currentCell, Cell *targetCell) {
	if(energy <= rules->movingEnergyCost) return false;

	if(!targetCell->haveAnimal()) {
		currentCell->removeAnimal();
		targetCell->animal = this;

		return true;
	}

	return false;
}

bool Animal::randomMove(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	int index = Random::rangeInt(0, neighbords.size() - 1);
	return move(currentCell, neighbords[index]);
}

bool Animal::canReproduce() {
	return (energy - rules->marginReproductionEnergy) >= rules->reproduicngEnergyCost
		&& reproductionCD <= 0;
}

bool Animal::canReproduceWith(Cell *cell) {
	if(!cell->haveAnimal()) return false;

	Animal *other = cell->animal;
	if(specie != other->getSpecie()) return false;
	if(!canReproduce() || !canReproduce()) return false;

	return true;
}

Cell *Animal::searchMate(std::vector<Cell *> const &neighbords) {
	for(Cell *cell : neighbords) {
		if(canReproduceWith(cell)) return cell;
	}

	return nullptr;
}

void Animal::reproducing() {
	energy -= rules->reproduicngEnergyCost;
	reproductionCD = Random::rangeInt(rules->reproductionCDRange);
}

std::ostream &operator<<(std::ostream &os, Animal const &a) {
	switch(a.specie) {
		case Animal::Species::BUNNY:
			os << "B";
			break;

		case Animal::Species::FOX:
			os << "F";
			break;
	}
	
	return os;
}
