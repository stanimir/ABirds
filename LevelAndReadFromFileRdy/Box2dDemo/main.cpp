#include "Box2D\Box2D.h"
#include "Game.h"
#include "BoxPhysics.h"

#include <iostream>

int main(int argc, const char * argv[])
{
	Game* game = new Game(1600, 900);
	
	game->GameLoop();

	return 0;
}