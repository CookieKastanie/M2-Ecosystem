#include "Ecosystem/entities/Entity.hpp"

Entity::Entity(): updateState{0}, dead{false} {

}

Entity::~Entity() {

}

char Entity::getState() {
	return updateState;
}

void Entity::setState(char s) {
	updateState = s;
}

bool Entity::isDead() {
	return dead;
}

void Entity::die() {
	dead = true;
}

Akila::Transform &Entity::getGraphicTransform() {
	return graphicTransform;
}

Cell *Entity::searchEmptyAnimalCell(std::vector<Cell *> const &neighbords) {
	for(Cell *cell : neighbords) {
		if(!cell->haveAnimal()) return cell;
	}

	return nullptr;
}

Cell *Entity::searchEmptyVegetalCell(std::vector<Cell *> const &neighbords) {
	for(Cell *cell : neighbords) {
		if(!cell->haveVegetal()) return cell;
	}

	return nullptr;
}
