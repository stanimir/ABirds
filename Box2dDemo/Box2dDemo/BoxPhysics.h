#pragma once
#include "Box2D\Box2D.h"
class BoxPhysics
{
public:
	BoxPhysics();
	~BoxPhysics();

	b2World* world = nullptr;
	b2Body* groundBody;
	b2Body* body;
	void createGndBody();
	void createBody();


private:

};

