#include <Ecosystem/entities/Vegetal.hpp>
#include "Ecosystem/utils/Random.hpp"

Vegetal::Vegetal(Vegetal::Rules *rules): rules{rules} {
	ttl = Random::rangeInt(rules->initialTTLRange);
	spraySeedCD = Random::rangeInt(rules->spraySeedCDRange);
}

void Vegetal::update(Cell *currentCell, std::vector<Cell *> const &neighbords) {
	--spraySeedCD;
	spraySeed(neighbords);
	if(spraySeedCD < 0) spraySeedCD = Random::rangeInt(rules->spraySeedCDRange);

	--ttl;
	if(ttl <= 0) die();
}

bool Vegetal::canSpraySeed() {
	return spraySeedCD <= 0;
}

bool Vegetal::spraySeed(std::vector<Cell *> const &neighbords) {
	if(!canSpraySeed()) return false;

	for(Cell *cell : neighbords) {
		if(!cell->haveVegetal()) {
			cell->vegetal = new Vegetal{rules};
			spraySeedCD = Random::rangeInt(rules->spraySeedCDRange);
			return true;
		}
	}

	return false;
}

std::ostream &operator<<(std::ostream &os, Vegetal const &v) {
	os << "V";
	return os;
}
