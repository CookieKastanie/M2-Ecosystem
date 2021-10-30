#pragma once

#include <vector>
#include <Ecosystem/entities/Animal.hpp>
#include <Ecosystem/entities/Vegetal.hpp>

#include <functional>	

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
	std::vector<Cell*> neighbords;

	char state;

	CreationProbabilities probs;

	Animal::Rules bunnyRules;
	Animal::Rules foxRules;
	Vegetal::Rules plantRules;

	Cell &Terrain::at(int x, int y);

public:
	Terrain(unsigned int size);

	void reset();

	void update();
	void print();

	int getSize();

	void setDefaultCreationProbs();
	CreationProbabilities &getCreationProbs();

	void setDefaultBunnyRules();
	void setDefaultFoxRules();
	void setDefaultPlantRules();

	Animal::Rules &getBunnyRules();
	Animal::Rules &getFoxRules();
	Vegetal::Rules &getPlantRules();

	void foreach(std::function<void(Cell *, int, int)> cb);
};
