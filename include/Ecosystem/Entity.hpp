#pragma once

class Entity {
private:
	char updateState;
	bool dead;

public:
	Entity();
	virtual ~Entity();

	char getState();
	void setState(char s);

	bool isDead();
	void die();	
};
