#pragma once

#include <iostream>
#include "Ecosystem/entities/Entity.hpp"
#include "Ecosystem/simulation/Cell.hpp"
#include <vector>

class Vegetal: public Entity {
public:
	struct Rules {
		int initialTTLRange[2];
		int spraySeedCDRange[2];
	};

private:
	Rules *rules;

	int ttl;
	int spraySeedCD;

public:
	Vegetal(Rules *rules);
	void update(Cell *currentCell, std::vector<Cell *> const &neighbords);
	friend std::ostream &operator<<(std::ostream &os, Vegetal const &v);

private:
	bool canSpraySeed();
	bool spraySeed(std::vector<Cell *> const &neighbords);
};
