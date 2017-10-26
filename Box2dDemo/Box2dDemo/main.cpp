#include "Box2D\Box2D.h"
#include "Game.h"
#include "BoxPhysics.h"

#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{
	Game* game = new Game(1280, 800);
	
	game->GameLoop();

	return 0;
}