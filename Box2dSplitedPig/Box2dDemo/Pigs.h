#pragma once
#include "BoxPhysics.h"

class Pigs : BoxPhysics
{
public:
	Pigs(b2World& world, int xpos, int ypos);
	~Pigs();

	b2Body* pigBody;

	int pigUserData = 2;

private:
	void createPig(b2World& world, int xpos, int ypos);
};

