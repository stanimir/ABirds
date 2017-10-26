#include "BoxPhysics.h"



BoxPhysics::BoxPhysics()
{
	b2Vec2 gravity(0.0f, 9.8f);
	world = new b2World(gravity);
	createGndBody();
	createBody();
}


BoxPhysics::~BoxPhysics()
{
}

void BoxPhysics::createGndBody()
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 7.0f);
	groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 0.1f);

	groundBody->CreateFixture(&groundBox, 0.0f);
}

void BoxPhysics::createBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(3.0f, 3.0f);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.45f, 1.28f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.0f;
	body->CreateFixture(&fixtureDef);
}
