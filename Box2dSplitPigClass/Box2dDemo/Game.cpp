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
	slingshotBox = new Sprite(csdl_setup->GetRenderer(), "ground.png", 700, 700, 25, 25);
	box[0] = new Sprite(csdl_setup->GetRenderer(), "bird.png", 400, 400, 25, 25);
	pigsSprite[0] = new Sprite(csdl_setup->GetRenderer(), "pig.png", 950, 500, 25, 25);
	pigWall[0] = new Sprite(csdl_setup->GetRenderer(), "ground.png", 900, 500, 10, 50);
	physics = new BoxPhysics();
	pigsObj = new Pigs();

}


Game::~Game()
{
	physics->world->DestroyBody(physics->bird[0]);
	physics->world->DestroyBody(physics->bottomfloor);
	physics->world->DestroyBody(physics->middleWall);
	physics->world->DestroyBody(physics->rightWall);
}

void Game::GameLoop()
{

	bool isButtonDown = false;
	bool isBirdActive = true;
	bool isBirdFlying = true;
	while (!quit &&csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		switch (csdl_setup->GetMainEvent()->type)
		{

		case SDL_MOUSEBUTTONDOWN:
		{
			if (isButtonDown == false) {
				isButtonDown = true;
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
			if (csdl_setup->GetMainEvent()->motion.state & SDL_BUTTON_LMASK & isButtonDown) {
				int x = csdl_setup->GetMainEvent()->button.x;
				int y = csdl_setup->GetMainEvent()->button.y;
				//std::cout << "X: " << x;
				//std::cout << " Y: " << y << std::endl;
				b2Vec2 temp = b2Vec2(x*P2M, y*P2M);
				physics->bird[0]->SetTransform(temp, physics->bird[0]->GetAngle());
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			if (isButtonDown == true) {
				isButtonDown = false;
				if (physics->distJoint != NULL) {
					physics->world->DestroyJoint(physics->distJoint);
					physics->distJoint = NULL;
				}
			}
			isBirdFlying = false;
			break;
		}

		default:
			break;
		}

		starting_tick = SDL_GetTicks();

		csdl_setup->Begin();

		background->Draw();
		ground->Draw();
		b2Vec2 birdTemp = physics->bird[0]->GetPosition();

		drawWithPhysics(physics->middleWall, slingshotBox, 0, 0);

		/*b2Vec2 walltemp = physics->middleWall->GetPosition();
		float wallTempAngle = 0 + (physics->middleWall->GetAngle() * RADTODEG);
		slingshotBox->Draw(walltemp, wallTempAngle);*/

		drawWithPhysics(physics->walls[0], pigWall[0], 15, -25);

		/*b2Vec2 pigwalltemp = physics->walls[0]->GetPosition();
		pigwalltemp.y -= 25 * P2M;
		float pigwallCurrentAngle = 0 + (physics->walls[0]->GetAngle() * RADTODEG);
		pigWall[0]->Draw(pigwalltemp, pigwallCurrentAngle);*/

		if (isBirdActive) {
			drawWithPhysics(physics->bird[0], box[0], 0, 0);
		}

		drawWithPhysics(pigsObj->pig, pigsSprite[0], 0, 0);
		/*b2Vec2 pigtemp = pigsObj->pig->GetPosition();
		std::cout << "X: " << pigtemp.x << " Y: " << pigtemp.y << std::endl;*/
		/*float pigCurrentAngle = 0 + (pigs->pigs[0]->GetAngle() * RADTODEG);
		pigsSprite[0]->Draw(pigtemp, pigCurrentAngle);*/


		physics->world->Step(timestep, velocityiterations, positioniterations);

		b2Vec2 afterBirdTemp = physics->bird[0]->GetPosition();

		/*if (afterBirdTemp == birdTemp && isBirdFlying == false) {
			isBirdActive = false;
			physics->bird[0]->SetActive(false);
		}*/


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

void Game::drawWithPhysics(b2Body * currBody, Sprite* currSprite, float xCorrection, float yCorrection)
{
	b2Vec2 temp = currBody->GetPosition();
	temp.x += xCorrection * P2M;
	temp.y += yCorrection * P2M;
	float tempAngle = 0 + (currBody->GetAngle() * RADTODEG);
	currSprite->Draw(temp, tempAngle);
}
