#include "BoxPhysics.h"

myContactListener myContactListenerInstance;

BoxPhysics::BoxPhysics()
{
	b2Vec2 gravity(0.0f, 9.8f);
	world = new b2World(gravity);

	world->SetContactListener(&myContactListenerInstance);

	nullAllB2Objects();
	createBottomFloor();
	createLeftWall();
	createRightWall();
	createTopWall();
	createMiddleWall();
	//createAnotherMiddleWall();
	createBird();
	createPigWalls(900, 500, 10, 50, 1.0f, 0.3f, 0.0f);
	createDistanceJoint(bird[0], middleWall);
	//createPiglet();
}


BoxPhysics::~BoxPhysics()
{

}

void BoxPhysics::nullAllB2Objects()
{
	bottomfloor = nullptr;
	leftWall = nullptr;
	rightWall = nullptr;
	middleWall = nullptr;
	anotherMiddleWall = nullptr;
	topWall = nullptr;
	bird[0] = nullptr;
	mouseJoint = nullptr;
	distJoint = nullptr;
}

void BoxPhysics::createBottomFloor()
{
	b2BodyDef bottomFloorDef;
	bottomFloorDef.type = b2_staticBody;
	bottomFloorDef.position.Set(0 * P2M, 675 * P2M);
	bottomfloor = world->CreateBody(&bottomFloorDef);

	b2EdgeShape bottomEdge;
	bottomEdge.Set(b2Vec2(0 * P2M, 0 * P2M), b2Vec2(1600 * P2M, 0 * P2M));

	bottomfloor->CreateFixture(&bottomEdge, 0.0f);
}

void BoxPhysics::createLeftWall()
{
	b2BodyDef leftWallDef;
	leftWallDef.position.Set(-25 * P2M, 0 * P2M);
	leftWall = world->CreateBody(&leftWallDef);

	b2EdgeShape leftEdge;
	leftEdge.Set(b2Vec2(0 * P2M, 0 * P2M), b2Vec2(0 * P2M, 700 * P2M));

	leftWall->CreateFixture(&leftEdge, 0.0f);
}

void BoxPhysics::createRightWall()
{
	b2BodyDef rightWallDef;
	rightWallDef.position.Set(1575 * P2M, 0 * P2M);
	rightWall = world->CreateBody(&rightWallDef);

	b2EdgeShape rightEdge;
	rightEdge.Set(b2Vec2(0 * P2M, 0 * P2M), b2Vec2(0 * P2M, 700 * P2M));

	rightWall->CreateFixture(&rightEdge, 0 * P2M);
}

void BoxPhysics::createTopWall()
{
	b2BodyDef topCeilingDef;
	topCeilingDef.position.Set(0 * P2M, 0 * P2M);
	topWall = world->CreateBody(&topCeilingDef);

	b2EdgeShape topEdge;
	topEdge.Set(b2Vec2(0 * P2M, 0 * P2M), b2Vec2(1600 * P2M, 0 * P2M));

	topWall->CreateFixture(&topEdge, 0.0f);
}

void BoxPhysics::createMiddleWall()
{
	b2BodyDef middleWallDef;
	middleWallDef.type = b2_staticBody;
	middleWallDef.position.Set(400 * P2M, 400 * P2M);
	middleWall = world->CreateBody(&middleWallDef);

	b2PolygonShape staticBody;
	staticBody.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef sfixtureDef;
	sfixtureDef.filter.maskBits = 0x0000;
	sfixtureDef.shape = &staticBody;
	sfixtureDef.density = 1.0f;
	middleWall->CreateFixture(&sfixtureDef);


}

void BoxPhysics::createAnotherMiddleWall()
{
	b2BodyDef amiddleWallDef;
	amiddleWallDef.type = b2_staticBody;
	amiddleWallDef.position.Set(625 * P2M, 483 * P2M);
	anotherMiddleWall = world->CreateBody(&amiddleWallDef);

	b2PolygonShape staticBody;
	staticBody.SetAsBox(P2M * 40, P2M * 190);
	b2FixtureDef sfixtureDef;
	sfixtureDef.shape = &staticBody;
	sfixtureDef.density = 1.0f;
	sfixtureDef.restitution = 0.0f;
	anotherMiddleWall->CreateFixture(&sfixtureDef);
}

void BoxPhysics::createBird()
{
	if (numOfBirds > 3) {
		return;
	}
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(400 * P2M, 400 * P2M);
	bird[0] = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	bird[0]->CreateFixture(&fixtureDef);
	numOfBirds++;
}

void BoxPhysics::createDistanceJoint(b2Body* target1, b2Body* target2)
{
	b2DistanceJointDef jointDef;
	b2Vec2 anchor1 = target1->GetWorldCenter();
	anchor1.x += 24 * P2M;
	b2Vec2 anchor2 = target2->GetWorldCenter();
	jointDef.Initialize(target1, target2, anchor1, anchor2);
	jointDef.length = 0.0f;
	jointDef.dampingRatio = 0.5f;
	jointDef.frequencyHz = 1.2f;
	distJoint = (b2DistanceJoint*)(world->CreateJoint(&jointDef));
}

void BoxPhysics::createPigWalls(int x, int y, int sizeX, int sizeY, float density, float friction, float restitution)
{
	if (numOfWalls > 4) {
		return;
	}
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	walls[numOfWalls] = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * sizeX, P2M * sizeY);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	walls[numOfWalls]->CreateFixture(&fixtureDef);
	numOfWalls++;
}

/*void BoxPhysics::createPiglet()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(950 * P2M, 500 * P2M);
	piglet = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	piglet->CreateFixture(&fixtureDef);
}*/


