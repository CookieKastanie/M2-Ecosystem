#pragma once

#include "Ecosystem/simulation/Cell.hpp"
#include <vector>

class Entity {
private:
	char updateState;
	bool dead;

public:
	Entity();
	virtual ~Entity();

	char getState();
	void setState(char s);

	bool isDead();
	void die();	

protected:
	Cell *searchEmptyAnimalCell(std::vector<Cell *> const &neighbords);
	Cell *searchEmptyVegetalCell(std::vector<Cell *> const &neighbords);
};
