#include "Pigs.h"

Pigs::Pigs()
{
	createPig();
	//createPig(950, 500, 25, 25, 1.0f, 0.3f, 0.0f);
}


Pigs::~Pigs()
{
}

void Pigs::createPig()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(950 * P2M, 500 * P2M);
	pig = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	pig->CreateFixture(&fixtureDef);
}


/*void Pigs::createPig(int x, int y, int sizeX, int sizeY, float density, float friction, float restitution)
{
	if (numOfPigs > 3) {
		return;
	}
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	pigs[numOfPigs] = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * sizeX, P2M * sizeY);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	pigs[numOfPigs]->CreateFixture(&fixtureDef);
	numOfPigs++;
}*/