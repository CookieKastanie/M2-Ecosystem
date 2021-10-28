#pragma once

#include "Animal.hpp"

class Bunny: public Animal {
public:
	Bunny(Rules *rules);

protected:
	void onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbords) override;

	bool eat(Cell *currentCell);
	bool reproduce(std::vector<Cell *> const &neighbords);
};
