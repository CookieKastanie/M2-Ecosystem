#include <Ecosystem/entities/Vegetal.hpp>
#include "Ecosystem/utils/Random.hpp"

Vegetal::Vegetal() {
	spraySeedRT = Random::rangeInt(5, 15);
}

void Vegetal::update(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	trySpraySeed(neighbords);
	--spraySeedRT;

	if(spraySeedRT < 0) spraySeedRT += Random::rangeInt(10, 20);
}

bool Vegetal::trySpraySeed(std::vector<Cell *> const &neighbords) {
	if(spraySeedRT > 0) return false;

	for(Cell *cell : neighbords) {
		if(!cell->haveVegetal()) {
			cell->vegetal = new Vegetal{};
			spraySeedRT = Random::rangeInt(10, 20);
			return true;
		}
	}

	return false;
}

std::ostream &operator<<(std::ostream &os, Vegetal const &v) {
	os << "V";
	return os;
}
