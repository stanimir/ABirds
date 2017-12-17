#pragma once
#include "Box2D\Box2D.h"
#include <vector>
#include "myContactListener.h"

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
	b2Body* slingshotBody;
	b2Body* topWall;
	b2RopeJoint* ropeJoint;

	int numOfWalls = 0;

	int slingshotUserData = 3;
	int wallUserData = 6;


	void nullAllB2Objects();
	void createBottomFloor();
	void createLeftWall();
	void createRightWall();
	void createslingshotBody();
	void createTopWall();
	void createRopeJoint(b2Body* body1, b2Body* body2);
};

