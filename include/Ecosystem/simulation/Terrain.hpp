#pragma once

#include <vector>
#include <Ecosystem/entities/Animal.hpp>
#include <Ecosystem/entities/Vegetal.hpp>

class Terrain {
public:
	struct CreationProbabilities {
		float bunny;
		float fox;
		float plant;
	};

private:
	std::size_t size;
	std::vector<Cell> cells;
	std::vector<Cell*> neighbors;

	char state;

	CreationProbabilities *probs;

	Animal::Rules *bunnyRules;
	Animal::Rules *foxRules;
	Vegetal::Rules *plantRules;

	Cell &Terrain::at(int x, int y);

public:
	Terrain(unsigned int size,
			CreationProbabilities *probs,
			Animal::Rules *bunnyRules,
			Animal::Rules *foxRules,
			Vegetal::Rules *plantRules);
	~Terrain();

	void reset(int newSize);
	void reset();

	void update();

	int getSize();

	std::vector<Cell> &getCells();

	friend std::ostream &operator<<(std::ostream &os, Terrain &terrain);
};
