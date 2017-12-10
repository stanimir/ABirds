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
	void CreateSprite(std::vector<Sprite*>& temp, std::string filename, int x, int y, int w, int h);

private:
	int ScreenWidth;
	int ScreenHeight;
	Uint32 starting_tick;
	bool quit;
	bool isButtonDown = false;
	bool isBirdActive = true;
	bool isBirdFlying = true;
	int pigDead = 4;

	void cap_framerate(Uint32 starting_tick);
	void drawWithPhysics(b2Body* currBody, Sprite* currSprite, float minusX, float minusY);
	void drawLevel();

	Sprite* background;
	
	Sprite* ground;
	Sprite* slingshotBox;
	Sprite* anotherMiddleWall;
	CSDL_Setup* csdl_setup;
	BoxPhysics* physics;
	std::vector<Pigs*> pigObj;

	std::vector<Sprite*> birdSprites;
	std::vector<Sprite*> pigSprites;
	std::vector<Sprite*> redPigSprites;
	std::vector<Sprite*> pigWallSprites;
};

