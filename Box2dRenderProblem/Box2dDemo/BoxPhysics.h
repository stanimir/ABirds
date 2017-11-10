#pragma once
#include "Box2D\Box2D.h"

const float M2P = 100;
const float P2M = 1 / M2P;
const float DEGTORAD =  0.0174532925199432957f;
const float RADTODEG = 57.295779513082320876f;

class BoxPhysics
{
public:
	BoxPhysics();
	~BoxPhysics();

	b2World* world;

	b2Body* bottomfloor;
	b2Body* leftWall;
	b2Body* rightWall;
	b2Body* middleWall;
	b2Body* anotherMiddleWall;
	b2Body* topWall;
	b2Body* bird;
	b2Body* groundBody;
	b2MouseJoint* mouseJoint;

	void createBottomFloor();
	void createLeftWall();
	void createRightWall();
	void createMiddleWall();
	void createAnotherMiddleWall();
	void createTopWall();
	void createBody();
	void createMouseJoint(/*const b2Vec2& p*/);

};

