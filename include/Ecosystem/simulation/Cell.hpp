#pragma once

#include <iostream>

class Animal;
class Vegetal;

struct Cell {
	Animal *animal;
	Vegetal *vegetal;

	Cell();
	~Cell();

	bool haveAnimal();
	bool haveVegetal();

	void removeAnimal();
	void removeVegetal();

	void deleteAnimal();
	void deleteVegetal();

	friend std::ostream &operator<<(std::ostream &os, Cell const &cell);
};
