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
	createslingshotBody();
}


BoxPhysics::~BoxPhysics()
{

}

void BoxPhysics::nullAllB2Objects()
{
	bottomfloor = nullptr;
	leftWall = nullptr;
	rightWall = nullptr;
	slingshotBody = nullptr;
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

void BoxPhysics::createslingshotBody()
{
	b2BodyDef middleWallDef;
	middleWallDef.type = b2_staticBody;
	middleWallDef.position.Set(400 * P2M, 400 * P2M);
	slingshotBody = world->CreateBody(&middleWallDef);
	slingshotBody->SetUserData(&slingshotUserData);

	b2PolygonShape staticBody;
	staticBody.SetAsBox(P2M * 25, P2M * 25);
	b2FixtureDef sfixtureDef;
	sfixtureDef.filter.maskBits = 0x0000;
	sfixtureDef.shape = &staticBody;
	sfixtureDef.density = 1.0f;
	slingshotBody->CreateFixture(&sfixtureDef);
}

void BoxPhysics::createRopeJoint(b2Body* body1, b2Body* body2)
{
	b2RopeJointDef ropeDef;
	ropeDef.bodyA = body1;
	ropeDef.bodyB = body2;
	ropeDef.maxLength = 100 * P2M;
	ropeDef.collideConnected = true;
	ropeDef.localAnchorA.Set(0.0f, 0.0f);
	ropeDef.localAnchorB.Set(0.0f, 0.0f);
	ropeJoint = (b2RopeJoint*) (world->CreateJoint(&ropeDef));
}
