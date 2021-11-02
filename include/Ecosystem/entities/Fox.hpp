#pragma once

#include "Animal.hpp"

class Fox: public Animal {
public:
	Fox(Rules *rules);

protected:
	void onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbors) override;

	bool eat(std::vector<Cell *> const &neighbors);
	Animal *instanciateOther() override;
};
