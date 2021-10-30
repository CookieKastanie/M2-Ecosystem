#include "Ecosystem/entities/Fox.hpp"

Fox::Fox(Rules *rules): Animal{Species::FOX, rules} {

}

void Fox::onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	int done = true;

	done = eat(neighbords);
	if(!done) done = reproduce(neighbords);
	if(!done) done = randomMove(currentCell, neighbords);
}

bool Fox::eat(std::vector<Cell *> const &neighbords) {
	if(energy >= rules->maxEnergy) return false;

	Animal *food = nullptr;

	for(Cell *cell : neighbords) {
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

bool Fox::reproduce(std::vector<Cell *> const &neighbords) {
	Cell *mateCell = searchMate(neighbords);
	Cell *emptyCell = searchEmptyAnimalCell(neighbords);

	if(mateCell != nullptr && emptyCell != nullptr) {
		emptyCell->animal = new Fox{rules};

		reproducing();
		static_cast<Fox *>(mateCell->animal)->reproducing();

		return true;
	}

	return false;
}
