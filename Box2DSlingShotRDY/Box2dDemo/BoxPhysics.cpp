#include "BoxPhysics.h"

myContactListener myContactListenerInstance;

BoxPhysics::BoxPhysics()
{
	//int pigID = 2;
	b2Vec2 gravity(0.0f, 9.8f);
	world = new b2World(gravity);

	world->SetContactListener(&myContactListenerInstance);

	nullAllB2Objects();
	createBottomFloor();
	createLeftWall();
	createRightWall();
	createTopWall();
	createMiddleWall();
	createBird();
	createPigWalls(900, 500, 10, 50, 1.0f, 0.3f, 0.0f);
	createRopeJoint();
	createPiglet();
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
	topWall = nullptr;
	bird[0] = nullptr;
}

void BoxPhysics::createBottomFloor()
{
	b2BodyDef bottomFloorDef;
	bottomFloorDef.type = b2_staticBody;
	bottomFloorDef.position.Set(0 * P2M, 675 * P2M);
	bottomfloor = world->CreateBody(&bottomFloorDef);
	bottomfloor->SetUserData(&wallUserData);

	b2EdgeShape bottomEdge;
	bottomEdge.Set(b2Vec2(0 * P2M, 0 * P2M), b2Vec2(1600 * P2M, 0 * P2M));

	bottomfloor->CreateFixture(&bottomEdge, 0.0f);
}

void BoxPhysics::createLeftWall()
{
	b2BodyDef leftWallDef;
	leftWallDef.position.Set(-25 * P2M, 0 * P2M);
	leftWall = world->CreateBody(&leftWallDef);
	leftWall->SetUserData(&wallUserData);


	b2EdgeShape leftEdge;
	leftEdge.Set(b2Vec2(0 * P2M, 0 * P2M), b2Vec2(0 * P2M, 700 * P2M));

	leftWall->CreateFixture(&leftEdge, 0.0f);
}

void BoxPhysics::createRightWall()
{
	b2BodyDef rightWallDef;
	rightWallDef.position.Set(1575 * P2M, 0 * P2M);
	rightWall = world->CreateBody(&rightWallDef);
	rightWall->SetUserData(&wallUserData);


	b2EdgeShape rightEdge;
	rightEdge.Set(b2Vec2(0 * P2M, 0 * P2M), b2Vec2(0 * P2M, 700 * P2M));

	rightWall->CreateFixture(&rightEdge, 0 * P2M);
}

void BoxPhysics::createTopWall()
{
	b2BodyDef topCeilingDef;
	topCeilingDef.position.Set(0 * P2M, 0 * P2M);
	topWall = world->CreateBody(&topCeilingDef);
	topWall->SetUserData(&wallUserData);

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
	middleWall->SetUserData(&slingshotUserData);

	b2PolygonShape staticBody;
	staticBody.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef sfixtureDef;
	sfixtureDef.filter.maskBits = 0x0000;
	sfixtureDef.shape = &staticBody;
	sfixtureDef.density = 1.0f;
	middleWall->CreateFixture(&sfixtureDef);
}

void BoxPhysics::createBird()
{
	if (numOfBirds > 3) {
		return;
	}
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(400 * P2M, 325 * P2M);
	bird[0] = world->CreateBody(&bodyDef);
	bird[0]->SetUserData(&birdUserData);

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

void BoxPhysics::createRopeJoint()
{
	b2RopeJointDef ropeDef;
	ropeDef.bodyA = bird[0];
	ropeDef.bodyB = middleWall;
	ropeDef.maxLength = 100 * P2M;
	ropeDef.collideConnected = true;
	ropeDef.localAnchorA.Set(0.0f, 0.0f);
	ropeDef.localAnchorB.Set(0.0f, 0.0f);
	ropeJoint = (b2RopeJoint*) (world->CreateJoint(&ropeDef));

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
	walls[numOfWalls]->SetUserData(&pigWallUserData);

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

void BoxPhysics::createPiglet()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(950 * P2M, 500 * P2M);
	piglet = world->CreateBody(&bodyDef);
	piglet->SetUserData(&pigUserData);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	piglet->CreateFixture(&fixtureDef);
}