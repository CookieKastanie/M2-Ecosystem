#include "Ecosystem/simulation/Cell.hpp"
#include "Ecosystem/entities/Animal.hpp"
#include "Ecosystem/entities/Vegetal.hpp"

Cell::Cell(): animal{nullptr}, vegetal{nullptr} {

}

Cell::~Cell() {
	deleteAnimal();
	deleteVegetal();
}

bool Cell::haveAnimal() {
	return animal != nullptr;
}

bool Cell::haveVegetal() {
	return vegetal != nullptr;
}

void Cell::removeAnimal() {
	animal = nullptr;
}

void Cell::removeVegetal() {
	animal = nullptr;
}

void Cell::deleteAnimal() {
	if(animal != nullptr) {
		delete animal;
		animal = nullptr;
	}
}

void Cell::deleteVegetal() {
	if(vegetal != nullptr) {
		delete vegetal;
		vegetal = nullptr;
	}
}

std::ostream &operator<<(std::ostream &os, Cell const &cell) {
	if(cell.animal != nullptr && cell.vegetal != nullptr) {
		os << " X ";
	} else if(cell.animal != nullptr) {
		os << " " << *cell.animal << " ";
	} else if(cell.vegetal != nullptr) {
		os << " " << *cell.vegetal << " ";
	} else {
		os << " - ";
	}

	return os;
}
