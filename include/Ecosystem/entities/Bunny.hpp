#pragma once

#include "Animal.hpp"

class Bunny: public Animal {
public:
	Bunny(Rules *rules);

protected:
	void onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbors) override;

	bool eat(Cell *currentCell);
	Animal *instanciateOther() override;
};
