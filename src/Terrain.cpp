#include <Ecosystem/Terrain.hpp>
#include <Ecosystem/Random.hpp>
#include <iostream>

Terrain::Cell::Cell(): animal{ nullptr }, vegetal{ nullptr } {
	
}

Terrain::Terrain(unsigned int size): size{ size } {
	cells.resize((std::size_t)size * size);

	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			Cell &cell = cells[(std::size_t)y * size + x];

			float rng1 = Random::generate();

			if(rng1 > 0.6) {
				float rng2 = Random::generate();

				if(rng2 > .5) {
					cell.animal = new Animal{};
				} else {
					cell.vegetal = new Vegetal{};
				}
			}
		}
	}
}

void Terrain::print() {
	std::cout << "---------------------------------------" << std::endl;

	for(int y = 0; y < size; ++y) {
		for(int x = 0; x < size; ++x) {
			Cell &cell = cells[(std::size_t)y * size + x];
			if(cell.animal != nullptr && cell.vegetal != nullptr) {
				std::cout << " X ";
			} else if(cell.animal != nullptr) {
				std::cout << " A ";
			} else if(cell.vegetal != nullptr) {
				std::cout << " V ";
			} else {
				std::cout << "   ";
			}
		}

		std::cout << std::endl;
	}
}

