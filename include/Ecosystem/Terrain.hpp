#pragma once

#include <vector>
#include <Ecosystem/Animal.hpp>
#include <Ecosystem/Vegetal.hpp>

class Terrain {
private:
	std::size_t size;
	std::vector<Cell> cells;
	std::vector<Cell*> neighbords;

	char state;

	Cell &Terrain::at(int x, int y);

public:
	Terrain(unsigned int size);

	void update();
	void print();
};
