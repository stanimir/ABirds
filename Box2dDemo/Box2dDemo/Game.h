#pragma once
#include "CSDL_Setup.h"
#include "BoxPhysics.h"
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

	Sprite* background;
	Sprite* box;
	CSDL_Setup* csdl_setup;
	BoxPhysics* physics;
};

