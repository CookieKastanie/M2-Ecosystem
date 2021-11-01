#pragma once

#include <Ecosystem/simulation/Terrain.hpp>
#include <Ecosystem/entities/Animal.hpp>
#include <Ecosystem/entities/Vegetal.hpp>

class Simulation {
private:
	Terrain::CreationProbabilities probs;

	Animal::Rules bunnyRules;
	Animal::Rules foxRules;
	Vegetal::Rules plantRules;

	Terrain terrain;

	bool playing;

public:
	Simulation();

	void update();

	void play();
	void pause();

	bool isPlaying();

	void setDefaultCreationProbs();
	Terrain::CreationProbabilities &getCreationProbs();

	void setDefaultBunnyRules();
	void setDefaultFoxRules();
	void setDefaultPlantRules();

	Animal::Rules &getBunnyRules();
	Animal::Rules &getFoxRules();
	Vegetal::Rules &getPlantRules();

	Terrain &getTerrain();
};
