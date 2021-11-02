#include <Ecosystem/entities/Animal.hpp>
#include "Ecosystem/utils/Random.hpp"
#include "Ecosystem/entities/Vegetal.hpp"
#include "Ecosystem/utils/Random.hpp"

Animal::Animal(Species specie, Rules *rules): specie{ specie }, rules{ rules } {
	if(Random::greaterThan(.5)) sex = Sex::MALE;
	else sex = Sex::FEMALE;

	ttl = Random::rangeInt(rules->initialTTLRange);
	energy = Random::rangeInt(rules->initialEnergyRange);
	reproductionCD = Random::rangeInt(rules->reproductionCDRange);
}

Animal::~Animal() {

}

Animal::Species Animal::getSpecie() {
	return specie;
}

Animal::Sex Animal::getSex() {
	return sex;
}

void Animal::update(Cell *currentCell, std::vector<Cell *> const &neighbors) {
	graphicTransform.savePrevious();

	onUpdate(currentCell, neighbors);

	--ttl;
	--reproductionCD;
	--energy;
	if(energy <= 0 || ttl <= 0) die();

	graphicTransform.setPosition(currentCell->x, 0, currentCell->y);
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

bool Animal::randomMove(Cell *currentCell, std::vector<Cell *> const &neighbors) {
	int index = Random::rangeInt(0, neighbors.size() - 1);
	return move(currentCell, neighbors[index]);
}

bool Animal::canReproduce() {
	return (energy - rules->marginReproductionEnergy) >= rules->reproduicngEnergyCost
		&& reproductionCD <= 0;
}

bool Animal::canReproduceWith(Cell *cell) {
	if(!cell->haveAnimal()) return false;

	Animal *other = cell->animal;
	if(specie != other->getSpecie()) return false;
	if(sex == other->getSex()) return false;
	if(!canReproduce() || !canReproduce()) return false;

	return true;
}

Cell *Animal::searchMate(std::vector<Cell *> const &neighbors) {
	for(Cell *cell : neighbors) {
		if(canReproduceWith(cell)) return cell;
	}

	return nullptr;
}

bool Animal::reproduceWithRandom(std::vector<Cell *> const &neighbors) {
	Cell *mateCell = searchMate(neighbors);
	Cell *emptyCell = searchEmptyAnimalCell(neighbors);

	if(mateCell != nullptr && emptyCell != nullptr) {
		emptyCell->animal = instanciateOther();
		emptyCell->animal->getGraphicTransform().setPosition(emptyCell->x, 0, emptyCell->y);
		emptyCell->animal->getGraphicTransform().savePrevious();

		energy -= rules->reproduicngEnergyCost;
		reproductionCD = Random::rangeInt(rules->reproductionCDRange);

		Animal *mate = mateCell->animal;
		mate->energy -= mate->rules->reproduicngEnergyCost;
		mate->reproductionCD = Random::rangeInt(mate->rules->reproductionCDRange);

		return true;
	}

	return false;
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
