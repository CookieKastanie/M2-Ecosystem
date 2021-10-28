#include "Ecosystem/entities/Bunny.hpp"
#include "Ecosystem/entities/Vegetal.hpp"

Bunny::Bunny(Rules *rules): Animal{Species::BUNNY, rules} {
	
}

void Bunny::onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	int done = true;

	done = eat(currentCell);
	if(!done) done = reproduce(neighbords);
	if(!done) done = randomMove(currentCell, neighbords);
}

bool Bunny::eat(Cell *currentCell) {
	if(currentCell->haveVegetal() && energy < rules->maxEnergy) {
		energy += rules->eatingEnergyGain;
		currentCell->vegetal->die();

		return true;
	}

	return false;
}

bool Bunny::reproduce(std::vector<Cell *> const &neighbords) {
	Cell *mateCell = searchMate(neighbords);
	Cell *emptyCell = searchEmptyAnimalCell(neighbords);

	if(mateCell != nullptr && emptyCell != nullptr) {
		emptyCell->animal = new Bunny{rules};

		reproducing();
		static_cast<Bunny*>(mateCell->animal)->reproducing(); // bruh

		return true;
	}

	return false;
}
