#pragma once
#include "BoxPhysics.h"
#include <iostream>

class myContactListener : public b2ContactListener
{
public:
	myContactListener();
	~myContactListener();

	void BeginContact(b2Contact* contact);
};


