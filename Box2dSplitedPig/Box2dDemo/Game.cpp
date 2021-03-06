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
	ground = new Sprite(csdl_setup->GetRenderer(), "ground.png", 0, ScreenHeight-200, ScreenWidth, 1);
	slingshotBox = new Sprite(csdl_setup->GetRenderer(), "ground.png", 700, 700, 25, 25);
	//box[0] = new Sprite(csdl_setup->GetRenderer(), "bird.png", 400, 400, 25, 25);
	/*pigsSprite[0] = new Sprite(csdl_setup->GetRenderer(), "pig.png", 950, 500, 25, 25);
	pigWall[0] = new Sprite(csdl_setup->GetRenderer(), "ground.png", 900, 600, 10, 70);
	pigWall[1] = new Sprite(csdl_setup->GetRenderer(), "ground.png", 1000, 600, 10, 70);
	pigWall[2] = new Sprite(csdl_setup->GetRenderer(), "ground.png", 950, 525, 100, 10);*/
	physics = new BoxPhysics();
	pigObj.push_back(new Pigs(*physics->world, 850, 450));
	/*pigObj->createPig(*physics->world, 850, 450);
	pigObj->createPig(*physics->world, 680, 450);
	pigObj->createPig(*physics->world, 750, 450);*/

	for (int i = 0; i < physics->birdVector.size(); i++) {
		physics->birdVector[i]->SetAngularDamping(5.0f);
		CreateSprite(birdSprites, "bird.png", 400, 400, 25, 25);
	}

	for (int i = 0; i < physics->pigVector.size(); i++)
	{
		CreateSprite(pigSprites,"pig.png", 500, 500, 25, 25);
	}

	for (int i = 0; i < physics->pigWalls.size(); i++) {
		CreateSprite(pigWallSprites,"ground.png", 500, 500, 10, 70);
	}

	/*for (int i = 0; i < pigObj->redPigs.size(); i++)
	{
		CreateSprite(redPigSprites, "newpig.png", 600, 550, 25, 25);
	}*/

	CreateSprite(redPigSprites, "newpig.png", 600, 550, 25, 25);
}


Game::~Game()
{
	physics->world->DestroyBody(physics->bottomfloor);
	physics->world->DestroyBody(physics->middleWall);
	physics->world->DestroyBody(physics->rightWall);
}

void Game::GameLoop()
{
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
				if (x < 250) x = 250;
				if (x > 400) x = 400;
				if (y > 550) y = 550;
				if (y < 320) y = 320;
				b2Vec2 temp = b2Vec2(((x - 13)*P2M), ((y - 13)*P2M));
				physics->birdVector[0]->SetTransform(temp, physics->birdVector[0]->GetAngle());
				physics->birdVector[0]->SetLinearVelocity(b2Vec2(0, 0));
				/*if (physics->middleWall != NULL) {
					physics->middleWall->SetActive(false);
				}*/
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{

			if (isButtonDown == true) {
				isButtonDown = false;
				b2Vec2 birdLastPos = physics->birdVector[0]->GetPosition();
				b2Vec2 wallPos = physics->middleWall->GetPosition();

				b2Vec2 forceToApply = b2Vec2(((physics->middleWall->GetPosition().x - birdLastPos.x) * P2M), ((physics->middleWall->GetPosition().y - birdLastPos.y)*P2M));
				forceToApply.x *= 150;
				forceToApply.y *= 150;
				std::cout << "Xforce: " << forceToApply.x << " Yforce: " << forceToApply.y << std::endl;

				if (physics->ropeJoint != NULL) {
					physics->world->DestroyJoint(physics->ropeJoint);
					physics->ropeJoint = NULL;
				}

				physics->birdVector[0]->ApplyLinearImpulse(forceToApply, physics->birdVector[0]->GetWorldCenter(), true);
			}
			//isBirdFlying = false;
			break;
		}

		default:
			break;
		}

		starting_tick = SDL_GetTicks();

		csdl_setup->Begin();

		drawLevel();

		csdl_setup->End();

		cap_framerate(starting_tick);
	}
}


void Game::drawLevel()
{
	background->Draw();
	ground->Draw();
	b2Vec2 birdTemp = physics->birdVector[0]->GetPosition();

	drawWithPhysics(physics->middleWall, slingshotBox, 0, 0);

	for (int i = 0; i < physics->pigVector.size(); i++)
	{
		if (*(int*)physics->pigVector[i]->GetUserData() == 4) {
			physics->pigVector[i]->SetActive(false);
		}
		if (physics->pigVector[i]->IsActive()) {
			drawWithPhysics(physics->pigVector[i], pigSprites[i], 0, 0);
		}
	}

	for (int i = 0; i < physics->pigWalls.size(); i++) {
		drawWithPhysics(physics->pigWalls[i], pigWallSprites[i], 15, -45);
	}

	for (int i = 0; i < physics->birdVector.size(); i++)
	{
		if (*(int*)physics->birdVector[i]->GetUserData() == 4) {
			physics->birdVector[i]->SetActive(false);
		}
		if (physics->birdVector[i]->IsActive()) {
			//physics->birdVector[i]->SetAngularDamping(5.0f);
			drawWithPhysics(physics->birdVector[i], birdSprites[i], 0, 0);
		}
	}

	/*for (int i = 0; i < pigObj->redPigs.size(); i++) {
		drawWithPhysics(pigObj->redPigs[i], redPigSprites[i], 0, 0);
	}*/

	drawWithPhysics(pigObj[0]->pigBody, redPigSprites[0], 0, 0);
	

	physics->world->Step(timestep, velocityiterations, positioniterations);

	b2Vec2 afterBirdTemp = physics->birdVector[0]->GetPosition();

	/*if (afterBirdTemp == birdTemp && isBirdFlying == false) {
		physics->birdVector[0]->SetUserData(&pigDead);
	}*/
}

void Game::CreateSprite(std::vector<Sprite*>& temp, std::string filename, int x, int y, int w, int h)
{
	temp.push_back(new Sprite(csdl_setup->GetRenderer(), filename, x, y, w, h));
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


