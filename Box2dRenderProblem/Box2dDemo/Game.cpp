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
	anotherMiddleWall = new Sprite(csdl_setup->GetRenderer(), "ground.png", 700, 610, 40, 190);
	box = new Sprite(csdl_setup->GetRenderer(), "bird.png", 400, 400, 25, 25);
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

	bool isButtonDown = false;
	while (!quit &&csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{



		b2Vec2 birdtemp = b2Vec2(physics->bird->GetPosition());
		switch (csdl_setup->GetMainEvent()->type)
		{

			/*case SDL_MOUSEMOTION:
			{
			if (csdl_setup->GetMainEvent()->motion.state & SDL_BUTTON_LMASK) {
			int x = csdl_setup->GetMainEvent()->button.x;
			int y = csdl_setup->GetMainEvent()->button.y;
			std::cout << "X: " << x;
			std::cout << " Y: " << y << std::endl;
			b2Vec2 temp = b2Vec2(x*P2M, y*P2M);
			physics->bird->SetTransform(temp, physics->bird->GetAngle());

			break;
			}

			}

			case SDL_MOUSEBUTTONUP:
			{
			if (physics->distJoint != nullptr) {
			physics->world->DestroyJoint(physics->distJoint);
			}

			}*/
			/////////////////////////////////////////////////

		case SDL_MOUSEBUTTONDOWN:
		{
			if (isButtonDown == false) {
				isButtonDown = true;
				//std::cout << "ButtonDownisButtonDown: " << isButtonDown << std::endl;

			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
			if (csdl_setup->GetMainEvent()->motion.state & SDL_BUTTON_LMASK & isButtonDown) {
				int x = csdl_setup->GetMainEvent()->button.x;
				int y = csdl_setup->GetMainEvent()->button.y;
				std::cout << "X: " << x;
				std::cout << " Y: " << y << std::endl;
				//std::cout << "MouseMotionisButtonDown: " << isButtonDown << std::endl;
				//std::cout << "DistanceJoint: " << physics->distJoint->GetReactionForce(-timestep) << std::endl;
				b2Vec2 temp = b2Vec2(x*P2M, y*P2M);
				physics->bird->SetTransform(temp, physics->bird->GetAngle());
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			if (isButtonDown == true) {
				isButtonDown = false;
				//std::cout << "ButtonUpisButtonDown: " << isButtonDown << std::endl;
				if (physics->distJoint != NULL) {
					physics->world->DestroyJoint(physics->distJoint);
					physics->distJoint = NULL;
				}
			}
			break;
		}



		//case SDL_MOUSEBUTTONUP:
		//	
		//	/*std::cout << "Button up" <<x++ <<std::endl;
		//	if (physics->mouseJoint != NULL)
		//	{
		//		physics->world->DestroyJoint(physics->mouseJoint);
		//		physics->mouseJoint = NULL;
		//	}*/
		//	//physics->bird->ApplyLinearImpulse(b2Vec2(-0.5f, 0), physics->bird->GetWorldCenter(), true);

		//	if (physics->mouseJoint) {
		//		physics->world->DestroyJoint(physics->mouseJoint);
		//		physics->mouseJoint = NULL;
		//	}

		//	break;

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


		/*//if (physics->anotherMiddleWall->IsActive()) {
		b2Vec2 awalltemp = physics->anotherMiddleWall->GetPosition();
		awalltemp.y -= 165 * P2M;
		awalltemp.x -= 15 * P2M;
		float anotherMiddleWallAngle = 0 + (physics->anotherMiddleWall->GetAngle() * RADTODEG);
		anotherMiddleWall->Draw(awalltemp, anotherMiddleWallAngle);
		//}*/

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
