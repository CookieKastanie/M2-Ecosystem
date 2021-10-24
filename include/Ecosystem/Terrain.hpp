#pragma once

#include <vector>
#include <Ecosystem/Animal.hpp>
#include <Ecosystem/Vegetal.hpp>

class Terrain {
public:
	struct Cell {
		Animal *animal;
		Vegetal *vegetal;

		Cell();
	};



private:
	std::size_t size;
	std::vector<Cell> cells;

public:
	Terrain(unsigned int size);

	void print();
};
