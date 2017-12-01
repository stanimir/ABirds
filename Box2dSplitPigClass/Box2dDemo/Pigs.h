#pragma once
#include "BoxPhysics.h"

class Pigs : public BoxPhysics
{
public:
	Pigs();
	~Pigs();

	//b2Body* pigs[3];
	b2Body* pig;

	//int numOfPigs = 0;

	//void createPig(int x, int y, int sizeX, int sizeY, float density, float friction, float restitution);
	void createPig();
};

