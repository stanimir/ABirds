#pragma once
#include "CSDL_Setup.h"
#include "Sprite.h"
#undef main

class Game
{
public:
	Game(int passed_ScreenWidth, int passed_ScreenHeight);
	~Game();
	void GameLoop();

private:
	int ScreenWidth;
	int ScreenHeight;
	Uint32 starting_tick;
	bool quit;
	void cap_framerate(Uint32 starting_tick);
	void drawWithPhysics(b2Body* currBody, Sprite* currSprite, float minusX, float minusY);

	Sprite* background;
	Sprite* box[3];
	Sprite* pigsSprite[3];
	Sprite* pigWall[4];
	Sprite* ground;
	Sprite* slingshotBox;
	Sprite* anotherMiddleWall;
	CSDL_Setup* csdl_setup;
	BoxPhysics* physics;
	Pigs* pigsObj;
};

