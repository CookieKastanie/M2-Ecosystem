#pragma once

#include "Animal.hpp"

class Fox: public Animal {
public:
	Fox(Rules *rules);

protected:
	void onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbords) override;

	bool eat(std::vector<Cell *> const &neighbords);
	Animal *instanciateOther() override;
};
