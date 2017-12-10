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
	createBird();
	createPigWalls(900, 600, 10, 70);
	createPigWalls(1000, 600, 10, 70);
	//createPigWalls(950, 525, 100, 10);
	createPig(500, 500, 25, 25);
	createPig(600, 500, 25, 25);
	createPig(950, 500, 25, 25);
	createRopeJoint();
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
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(400 * P2M, 325 * P2M);
	int bsize = birdVector.size();
	birdVector.push_back(world->CreateBody(&bodyDef));
	birdVector[bsize]->SetUserData(&birdUserData);

	b2CircleShape circleShape;
	//dynamicBox.SetAsBox(P2M * 25, P2M * 25);
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 25 * P2M;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.1f;
	birdVector[bsize]->CreateFixture(&fixtureDef);
}

void BoxPhysics::createRopeJoint()
{
	b2RopeJointDef ropeDef;
	ropeDef.bodyA = birdVector[0];
	ropeDef.bodyB = middleWall;
	ropeDef.maxLength = 100 * P2M;
	ropeDef.collideConnected = true;
	ropeDef.localAnchorA.Set(0.0f, 0.0f);
	ropeDef.localAnchorB.Set(0.0f, 0.0f);
	ropeJoint = (b2RopeJoint*) (world->CreateJoint(&ropeDef));

}

void BoxPhysics::createPigWalls(int x, int y, int sizeX, int sizeY)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	int wsize = pigWalls.size();
	pigWalls.push_back(world->CreateBody(&bodyDef));
	pigWalls[wsize]->SetUserData(&pigWallUserData);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * sizeX, P2M * sizeY);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	pigWalls[wsize]->CreateFixture(&fixtureDef);
}

void BoxPhysics::createPig(int x, int y, int sizeX, int sizeY)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	int vsize = pigVector.size();
	pigVector.push_back(world->CreateBody(&bodyDef));
	pigVector[vsize]->SetUserData(&pigUserData);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * sizeX, P2M * sizeY);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	pigVector[vsize]->CreateFixture(&fixtureDef);
}
