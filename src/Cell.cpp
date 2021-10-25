#include "Ecosystem/Cell.hpp"
#include "Ecosystem/Animal.hpp"
#include "Ecosystem/Vegetal.hpp"

Cell::Cell(): animal{nullptr}, vegetal{nullptr} {

}

Cell::~Cell() {
	if(animal != nullptr) delete animal;
	if(vegetal != nullptr) delete vegetal;
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
