#pragma once
#include "Box2D\Box2D.h"
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
	b2Body* middleWall;
	b2Body* anotherMiddleWall;
	b2Body* topWall;
	b2Body* bird[3];
	b2Body* walls[4];
	b2Body* piglet;
	b2RopeJoint* ropeJoint;

	int numOfWalls = 0;
	int numOfBirds = 0;

	int birdUserData = 1;
	int pigUserData = 2;
	int slingshotUserData = 3;
	int pigDead = 4;
	int pigWallUserData = 5;
	int wallUserData = 6;


	void nullAllB2Objects();
	void createBottomFloor();
	void createLeftWall();
	void createRightWall();
	void createMiddleWall();
	//void createAnotherMiddleWall();
	void createTopWall();
	void createBird();
	void createRopeJoint();
	void createPigWalls(int x, int y, int sizeX, int sizeY, float density, float friction, float restitution);
	void createPiglet();

};

