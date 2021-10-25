#pragma once

#include <iostream>
#include "Ecosystem/Entity.hpp"
#include "Ecosystem/Cell.hpp"
#include <vector>

class Animal: public Entity {
public:
	enum class Species {
		MICE,
		FOX,
	};

private:
	Species specie;
	bool carnivorous;

	// Remaining Time
	int reproductionRT;
	int starvingRT;

public:
	Animal();
	void update(Cell *currentCell, std::vector<Cell*> const &neighbords);
	bool canReproduce();
	friend std::ostream &operator<<(std::ostream &os, Animal const &a);

private:
	bool randomMove(Cell *currentCell, std::vector<Cell *> const &neighbords);
	bool tryReproduce(std::vector<Cell *> const &neighbords);
	bool tryEat(Cell *currentCell);
};
