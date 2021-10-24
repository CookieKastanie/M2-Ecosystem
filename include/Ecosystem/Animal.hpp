#pragma once

class Animal {
public:
	enum class Species {
		A,
		B,
		C
	};

private:
	Species specie;
	bool carnivorous;

public:
	Animal();
};
