#pragma once

#include <iostream>
#include "Ecosystem/entities/Entity.hpp"
#include "Ecosystem/simulation/Cell.hpp"
#include <vector>

class Vegetal: public Entity {
private:
	int spraySeedRT;

public:
	Vegetal();
	void update(Cell *currentCell, std::vector<Cell *> const &neighbords);
	friend std::ostream &operator<<(std::ostream &os, Vegetal const &v);

private:
	bool trySpraySeed(std::vector<Cell *> const &neighbords);
};
