#include "Game.h"



Game::Game(int passed_ScreenWidth, int passed_ScreenHeight)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	background = new Sprite(csdl_setup->GetRenderer(), "background.png", 0, 0, ScreenWidth, ScreenHeight);

	box = new Sprite(csdl_setup->GetRenderer(), "sprite.png", 300, 300 , 148, 125);
	physics = new BoxPhysics();
}


Game::~Game()
{

}

void Game::GameLoop()
{
	while (!quit &&csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		starting_tick = SDL_GetTicks();

		csdl_setup->Begin();

		background->Draw();

		physics->world->Step(1.0f / 60.0f, 6, 2);

		b2Vec2 temp = physics->body->GetPosition();
		
		box->Draw(temp);
		
		//box->Draw();

		csdl_setup->End();

		cap_framerate(starting_tick);
	}
}

void Game::cap_framerate(Uint32 starting_tick)
{
	if ((1000 / 60) > SDL_GetTicks() - starting_tick)
	{
		SDL_Delay(1000 / 60 - (SDL_GetTicks() - starting_tick));
	}
}
