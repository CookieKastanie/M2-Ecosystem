#include "Ecosystem/entities/Bunny.hpp"
#include "Ecosystem/entities/Vegetal.hpp"

Bunny::Bunny(Rules *rules): Animal{Species::BUNNY, rules} {
	
}

void Bunny::onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbors) {
	int done = true;

	done = eat(currentCell);
	if(!done) done = reproduceWithRandom(neighbors);
	if(!done) done = randomMove(currentCell, neighbors);
}

bool Bunny::eat(Cell *currentCell) {
	if(currentCell->haveVegetal() && energy < rules->maxEnergy) {
		energy += rules->eatingEnergyGain;
		currentCell->vegetal->die();

		return true;
	}

	return false;
}

Animal *Bunny::instanciateOther() {
	return new Bunny{rules};
}
