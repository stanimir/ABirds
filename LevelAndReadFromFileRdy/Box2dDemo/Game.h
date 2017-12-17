#pragma once
#include "CSDL_Setup.h"
#include "Sprite.h"
#include "Birds.h"
#include "Pigs.h"
#include "PigWalls.h"

#undef main

class Game
{
public:
	Game(int passed_ScreenWidth, int passed_ScreenHeight);
	~Game();
	void GameLoop();

private:
	enum GameState {
		MainMenu,
		Level1,
		Level2,
		EndGame
	};

	int ScreenWidth;
	int ScreenHeight;
	Uint32 starting_tick;
	bool quit;
	bool isButtonDown = false;
	bool isBirdFlying = false;
	bool loadNextBird = false;
	bool isNextLevel = true;
	int worldbodycount = 0;
	int currentLvl = 0;
	int currentBird = 0;
	int maxBirds = 2;
	int pigDead = 4;

	int score = 0;

	void cap_framerate(Uint32 starting_tick);
	void drawWithPhysics(b2Body* currBody, Sprite* currSprite, float minusX, float minusY);
	//void drawSlingshot(b2Body* birdBody, b2Body* slingbody, Sprite* rubberband);
	void resetLevel();
	void loadNextLevel();
	void drawLevel();
	void loadFromFile();

	Sprite* background;
	Sprite* ground;
	Sprite* slingshotBox;
	Sprite* rubberA;

	CSDL_Setup* csdl_setup;

	BoxPhysics* physics;

	GameState gameState;

	std::vector<Pigs*> pigObj;
	std::vector<Birds*> birdObj;
	std::vector<PigWalls*> pigWallObj;
};

