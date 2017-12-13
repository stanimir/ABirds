#pragma once
#include "BoxPhysics.h"
#include "CSDL_Setup.h"
#include "Sprite.h"


class Birds
{
public:
	Birds(b2World& world, CSDL_Setup* csdl_setup, int xpos, int ypos);
	~Birds();

	int birdUserData = 1;

	b2Body* m_birdBody;
	Sprite* m_birdSprite;

private: 
	void createBird(b2World& world, int xpos, int ypos);
};

