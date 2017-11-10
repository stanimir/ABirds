#include "Game.h"

const int fps = 60;
const int velocityiterations = 10;
const int positioniterations = 8;
const float timestep = 1.0f / fps;

Game::Game(int passed_ScreenWidth, int passed_ScreenHeight)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	background = new Sprite(csdl_setup->GetRenderer(), "background.png", 0, 0, ScreenWidth, ScreenHeight);
	ground = new Sprite(csdl_setup->GetRenderer(), "ground.png", 0, 700, 1600, 1);
	middleWall = new Sprite(csdl_setup->GetRenderer(), "ground.png", 700, 700, 25, 25);
	anotherMiddleWall = new Sprite(csdl_setup->GetRenderer(), "ground.png", 700, 610, 25, 190);
	box = new Sprite(csdl_setup->GetRenderer(), "bird.png", 300, 300, 25, 25);
	physics = new BoxPhysics();
	//physics->createMouseJoint();

}


Game::~Game()
{
	physics->world->DestroyBody(physics->bird);
	physics->world->DestroyBody(physics->bottomfloor);
	physics->world->DestroyBody(physics->middleWall);
	physics->world->DestroyBody(physics->rightWall);
}

void Game::GameLoop()
{
	int x = 0;
	while (!quit &&csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		
		int mouse_x, mouse_y;
		int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

		b2Vec2 birdtemp = b2Vec2(physics->bird->GetPosition());
		switch (csdl_setup->GetMainEvent()->type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{

			//physics->createMouseJoint();
			int x = csdl_setup->GetMainEvent()->button.x;
			int y = csdl_setup->GetMainEvent()->button.y;


			physics->bird->ApplyLinearImpulse(b2Vec2(0.5f, 0), physics->bird->GetWorldCenter(), true);

			float birdAngle = 0 + (physics->bird->GetAngle() * RADTODEG);
			std::cout << "birdAngle: " << birdAngle << std::endl;

			float middletemp = 0 + (physics->middleWall->GetAngle() * RADTODEG);
			std::cout << "middletemp: " << middletemp << std::endl;

			float aMiddleWallAngle = 0 + (physics->anotherMiddleWall->GetAngle() * RADTODEG);
			std::cout << "aMiddleWallAngle: " << aMiddleWallAngle << std::endl;
			
			//float birdCurrentAngle = 360 - (physics->bird->GetAngle() * RADTODEG);
			//std::cout << "Angle: " <<birdCurrentAngle<< std::endl;
			
			/*b2Vec2 mousepos = b2Vec2(float((x / 100) - birdtemp.x), float((y / 100) - birdtemp.y));
			physics->mouseJoint->SetTarget(mousepos);*/



			/*if (physics->mouseJoint == NULL)
			{
				physics->createMouseJoint(b2Vec2(x, y));
			}*/

			break;
		}
		case SDL_MOUSEBUTTONUP:
			
			/*std::cout << "Button up" <<x++ <<std::endl;
			if (physics->mouseJoint != NULL)
			{
				physics->world->DestroyJoint(physics->mouseJoint);
				physics->mouseJoint = NULL;
			}*/
			//physics->bird->ApplyLinearImpulse(b2Vec2(-0.5f, 0), physics->bird->GetWorldCenter(), true);

			break;

		default:
			break;
		}

		//if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		//{
		//	/*int x, y;
		//	SDL_GetMouseState(&x, &y);
		//	if (physics->mouseJoint == NULL)
		//	{
		//		physics->createMouseJoint(b2Vec2(x, y));
		//	}*/
		//	b2Vec2 wallTemp = physics->middleWall->GetPosition();
		//	std::cout << wallTemp.x << " " << wallTemp.y << std::endl;

		//	physics->bird->ApplyLinearImpulse(b2Vec2(2, 0), physics->bird->GetWorldCenter(), true);
		//}

		//if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP)
		//{
		//	/*if (physics->mouseJoint != NULL)
		//	{
		//		physics->world->DestroyJoint(physics->mouseJoint);
		//		physics->mouseJoint = NULL;
		//	}*/

		//	physics->bird->ApplyLinearImpulse(b2Vec2(-2, 0), physics->bird->GetWorldCenter(), true);
		//}

		starting_tick = SDL_GetTicks();

		csdl_setup->Begin();

		background->Draw();
		ground->Draw();
		
		b2Vec2 walltemp = physics->middleWall->GetPosition();
		float wallTempAngle = 0 + (physics->middleWall->GetAngle() * RADTODEG);
		middleWall->Draw(walltemp, wallTempAngle);

		b2Vec2 awalltemp = physics->anotherMiddleWall->GetPosition();
		awalltemp.y -= 165 * P2M;
		float anotherMiddleWallAngle = 0 + (physics->anotherMiddleWall->GetAngle() * RADTODEG);
		anotherMiddleWall->Draw(awalltemp, anotherMiddleWallAngle);

		physics->world->Step(timestep, velocityiterations, positioniterations);

		b2Vec2 temp = physics->bird->GetPosition();
		float birdCurrentAngle = 0 + (physics->bird->GetAngle() * RADTODEG);
		box->Draw(temp, birdCurrentAngle);

		csdl_setup->End();

		cap_framerate(starting_tick);
	}
}

void Game::cap_framerate(Uint32 starting_tick)
{
	if ((1000 / fps) > SDL_GetTicks() - starting_tick)
	{
		SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
	}
}

//void Game::mousePress(SDL_MouseButtonEvent & b)
//{
//	if (b.button == SDL_BUTTON_LEFT)
//	{
//
//	}
//}
