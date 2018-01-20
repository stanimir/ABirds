#pragma once
#include "BoxPhysics.h"
#include "CSDL_Setup.h"
#include "Sprite.h"

class Pigs : BoxPhysics
{
public:
	Pigs(b2World& world, CSDL_Setup* csdl_setup, int xpos, int ypos);
	~Pigs();

	b2Body* m_pigBody;
	Sprite* m_pigSprite;
	Sprite* m_pigIdleAnimation;
	Sprite* m_pigDeathAnimation;

	int pigUserData = 2;

private:
	void createPig(b2World& world, int xpos, int ypos);
	
};

