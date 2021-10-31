#pragma once

#include <iostream>
#include "Ecosystem/entities/Entity.hpp"
#include "Ecosystem/simulation/Cell.hpp"
#include <vector>

class Animal: public Entity {
public:
	enum class Species {
		BUNNY,
		FOX,
	};

	enum class Sex {
		MALE,
		FEMALE
	};

	struct Rules {
		int initialTTLRange[2];
		int initialEnergyRange[2];

		int reproductionCDRange[2];

		int movingEnergyCost;
		int reproduicngEnergyCost;
		int marginReproductionEnergy;

		int eatingEnergyGain;
		int maxEnergy;
	};

protected:
	Species specie;
	Sex sex;
	Rules *rules;

	int ttl; // time to live
	int energy;

	int reproductionCD;

public:
	Animal(Species specie, Rules *rules);
	virtual ~Animal();

	Species getSpecie();
	Sex getSex();

	void update(Cell *currentCell, std::vector<Cell*> const &neighbords) override;

	friend std::ostream &operator<<(std::ostream &os, Animal const &a);

protected:
	virtual void onUpdate(Cell *currentCell, std::vector<Cell *> const &neighbords) = 0;

	bool move(Cell *currentCell, Cell *targetCell);
	bool randomMove(Cell *currentCell, std::vector<Cell *> const &neighbords);

	bool canReproduce();
	bool canReproduceWith(Cell *cell);
	Cell *searchMate(std::vector<Cell *> const &neighbords);
	virtual Animal *instanciateOther() = 0;
	bool reproduceWithRandom(std::vector<Cell *> const &neighbords);
};
