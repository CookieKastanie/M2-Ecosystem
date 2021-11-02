#pragma once

#include "Ecosystem/simulation/Cell.hpp"
#include <vector>
#include <Akila/entities/Transform.hpp>

class Entity {
private:
	char updateState;
	bool dead;

public:
	Entity();
	virtual ~Entity();

	char getState();
	void setState(char s);

	virtual void update(Cell *currentCell, std::vector<Cell *> const &neighbors) = 0;

	bool isDead();
	void die();

	Akila::Transform &getGraphicTransform();

protected:
	Akila::Transform graphicTransform;

	Cell *searchEmptyAnimalCell(std::vector<Cell *> const &neighbors);
	Cell *searchEmptyVegetalCell(std::vector<Cell *> const &neighbors);
};
