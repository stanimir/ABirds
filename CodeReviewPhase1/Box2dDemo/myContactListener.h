#pragma once
#include "BoxPhysics.h"
#include <iostream>

class myContactListener : public b2ContactListener
{
public:
	myContactListener();
	~myContactListener();

	int pigDead = 4;

	void BeginContact(b2Contact* contact);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};


