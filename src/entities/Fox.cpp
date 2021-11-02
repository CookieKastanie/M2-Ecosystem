#include "Ecosystem/entities/Fox.hpp"

Fox::Fox(Rules *rules): Animal{Species::FOX, rules} {

}

void Fox::onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbors) {
	int done = true;

	done = eat(neighbors);
	if(!done) done = reproduceWithRandom(neighbors);
	if(!done) done = randomMove(currentCell, neighbors);
}

bool Fox::eat(std::vector<Cell *> const &neighbors) {
	if(energy >= rules->maxEnergy) return false;

	Animal *food = nullptr;

	for(Cell *cell : neighbors) {
		if(cell->haveAnimal()) {
			if(cell->animal->getSpecie() == Species::BUNNY) {
				food = cell->animal;
			}
		}
	}

	if(food == nullptr) return false;

	energy += rules->eatingEnergyGain;
	food->die();

	return true;
}

Animal *Fox::instanciateOther() {
	return new Fox{rules};
}
