#include "Pigs.h"

Pigs::Pigs(b2World& world, int xpos, int ypos)
{
	createPig(world, xpos, ypos);
}


Pigs::~Pigs()
{
}

void Pigs::createPig(b2World& world, int xpos, int ypos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(xpos * P2M, ypos * P2M);
	pigBody = world.CreateBody(&bodyDef);
	pigBody->SetUserData(&pigUserData);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	pigBody->CreateFixture(&fixtureDef);
}