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
