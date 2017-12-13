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
	ground = new Sprite(csdl_setup->GetRenderer(), "ground.png", 0, ScreenHeight - 200, ScreenWidth, 1);
	slingshotBox = new Sprite(csdl_setup->GetRenderer(), "ground.png", 700, 700, 25, 25);
	rubberA = new Sprite(csdl_setup->GetRenderer(), "ground.png", 400, 400, 50, 5);


	physics = new BoxPhysics();

	birdObj.push_back(new Birds(*physics->world, csdl_setup, 400, 400));

	//physics->createRopeJoint(birdObj[0]->m_birdBody, physics->slingshotBody);

	pigObj.push_back(new Pigs(*physics->world, csdl_setup, 950, 600));
	pigObj.push_back(new Pigs(*physics->world, csdl_setup, 1100, 600));
	pigObj.push_back(new Pigs(*physics->world, csdl_setup, 1200, 600));

	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 900, 600, 10, 70));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 1000, 600, 10, 70));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 950, 520, 100, 10));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 900, 460, 10, 70));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 1000, 460, 10, 70));



	/*for (int i = 0; i < birdObj.size(); i++)
	{
		CreateSprite(birdSprites, "bird.png", 400, 400, 25, 25);
	}*/

	/*for (int i = 0; i < pigObj.size(); i++)
	{
		CreateSprite(redPigSprites, "pig.png", 500, 500, 25, 25);
	}*/

	/*for (int i = 0; i < pigWallObj.size(); i++)
	{
		CreateSprite(pigWallSprites, "ground.png", 500, 500, pigWallObj[i]->w, pigWallObj[i]->h);
	}*/

}


Game::~Game()
{
	physics->world->DestroyBody(physics->bottomfloor);
	physics->world->DestroyBody(physics->slingshotBody);
	physics->world->DestroyBody(physics->rightWall);
}

void Game::GameLoop()
{
	while (!quit &&csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		/*if (physics->ropeJoint == NULL && isBirdFlying == false) {
			physics->createRopeJoint(birdObj[currentBird]->m_birdBody, physics->slingshotBody);
		}*/

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
				birdObj[0]->m_birdBody->SetTransform(temp, birdObj[0]->m_birdBody->GetAngle());
				birdObj[0]->m_birdBody->SetLinearVelocity(b2Vec2(0, 0));

				//physics->birdVector[0]->SetTransform(temp, physics->birdVector[0]->GetAngle());
				//physics->birdVector[0]->SetLinearVelocity(b2Vec2(0, 0));

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
				b2Vec2 birdLastPos = birdObj[0]->m_birdBody->GetPosition();
				//b2Vec2 birdLastPos = physics->birdVector[0]->GetPosition();
				b2Vec2 wallPos = physics->slingshotBody->GetPosition();

				b2Vec2 forceToApply = b2Vec2(((physics->slingshotBody->GetPosition().x - birdLastPos.x) * P2M), ((physics->slingshotBody->GetPosition().y - birdLastPos.y)*P2M));
				forceToApply.x *= 150;
				forceToApply.y *= 150;
				std::cout << "Xforce: " << forceToApply.x << " Yforce: " << forceToApply.y << std::endl;

				if (physics->ropeJoint != NULL) {
					physics->world->DestroyJoint(physics->ropeJoint);
					physics->ropeJoint = NULL;
				}

				birdObj[0]->m_birdBody->ApplyLinearImpulse(forceToApply, birdObj[0]->m_birdBody->GetWorldCenter(), true);

				//physics->birdVector[0]->ApplyLinearImpulse(forceToApply, physics->birdVector[0]->GetWorldCenter(), true);
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

	b2Vec2 birdTemp = birdObj[0]->m_birdBody->GetPosition();

	drawWithPhysics(physics->slingshotBody, slingshotBox, 0, 0);

	for (int i = 0; i < pigObj.size(); i++)
	{
		if (*(int*)pigObj[i]->m_pigBody->GetUserData() == 4) {
			pigObj[i]->m_pigBody->SetActive(false);
		}
		if (pigObj[i]->m_pigBody->IsActive()) {
			drawWithPhysics(pigObj[i]->m_pigBody, pigObj[i]->m_pigSprite, 0, 0);
		}
	}

	for (int i = 0; i < pigWallObj.size(); i++) {
		drawWithPhysics(pigWallObj[i]->m_pigWallBody, pigWallObj[i]->m_pigWallSprite, (25- pigWallObj[i]->m_w), (25- pigWallObj[i]->m_h));
	}

	for (int i = 0; i < birdObj.size(); i++)
	{
		if (*(int*)birdObj[i]->m_birdBody->GetUserData() == 4) {
			birdObj[i]->m_birdBody->SetActive(false);
		}
		if (birdObj[i]->m_birdBody->IsActive()) {
			drawWithPhysics(birdObj[i]->m_birdBody, birdObj[i]->m_birdSprite, 0, 0);
		}
	}

	physics->world->Step(timestep, velocityiterations, positioniterations);

	b2Vec2 afterBirdTemp = birdObj[0]->m_birdBody->GetPosition();

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


