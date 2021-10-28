#pragma once

#include <vector>
#include <Ecosystem/entities/Animal.hpp>
#include <Ecosystem/entities/Vegetal.hpp>

#include <functional>	

class Terrain {
private:
	std::size_t size;
	std::vector<Cell> cells;
	std::vector<Cell*> neighbords;

	char state;

	Animal::Rules animalsRules;

	Cell &Terrain::at(int x, int y);

public:
	Terrain(unsigned int size);

	void reset();

	void update();
	void print();

	int getSize();

	void foreach(std::function<void(Cell *, int, int)> cb);
};
