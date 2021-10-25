#pragma once

#include <iostream>

class Animal;
class Vegetal;

struct Cell {
	Animal *animal;
	Vegetal *vegetal;

	Cell();
	~Cell();
	friend std::ostream &operator<<(std::ostream &os, Cell const &cell);
};
