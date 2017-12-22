#include "Game.h"
#include <string>
#include <fstream>
#include <sstream>

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

	/*physics = new BoxPhysics();
	loadFromFile();*/

	gameState = GameState::Level1;

	/*if (Mix_PlayMusic(csdl_setup->bgm, -1) == -1) {
		std::cout << "Mix_PlayMusic Error: " << Mix_GetError() << std::endl;
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

		if (isNextLevel == true && gameState != EndGame) {
			loadNextLevel();
			isNextLevel = false;
		}


		if (physics->ropeJoint == NULL && isBirdFlying == false && gameState != EndGame) {
			physics->createRopeJoint(birdObj[currentBird]->m_birdBody, physics->slingshotBody);
		}

		if (gameState != EndGame) {
			switch (csdl_setup->GetMainEvent()->type)
			{

			case SDL_MOUSEBUTTONDOWN:
			{
				if (isButtonDown == false) {
					isButtonDown = true;
					Mix_PlayChannel(-1, csdl_setup->rubberband, 0);
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
					b2Vec2 temp = b2Vec2(((x - 25)*P2M), ((y - 25)*P2M));
					birdObj[currentBird]->m_birdBody->SetTransform(temp, birdObj[currentBird]->m_birdBody->GetAngle());
					birdObj[currentBird]->m_birdBody->SetLinearVelocity(b2Vec2(0, 0));

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
					b2Vec2 birdLastPos = birdObj[currentBird]->m_birdBody->GetPosition();
					//b2Vec2 birdLastPos = physics->birdVector[0]->GetPosition();
					b2Vec2 wallPos = physics->slingshotBody->GetPosition();

					if (physics->ropeJoint != NULL) {
						physics->world->DestroyJoint(physics->ropeJoint);
						physics->ropeJoint = NULL;
					}

					b2Vec2 forceToApply = b2Vec2(((physics->slingshotBody->GetPosition().x - birdLastPos.x) * P2M), ((physics->slingshotBody->GetPosition().y - birdLastPos.y)*P2M));
					forceToApply.x *= 150;
					forceToApply.y *= 150;
					std::cout << "Xforce: " << forceToApply.x << " Yforce: " << forceToApply.y << std::endl;



					birdObj[currentBird]->m_birdBody->ApplyLinearImpulse(forceToApply, birdObj[currentBird]->m_birdBody->GetWorldCenter(), true);

					Mix_PlayChannel(-1, csdl_setup->birdflying, 0);

					//physics->birdVector[0]->ApplyLinearImpulse(forceToApply, physics->birdVector[0]->GetWorldCenter(), true);
					isBirdFlying = true;
				}
				break;
			}

			default:
				break;
			}
		}

		starting_tick = SDL_GetTicks();

		csdl_setup->Begin();



		switch (gameState)
		{
		case MainMenu:

			break;

		case Level1:
			drawLevel();
			if (isNextLevel == true) {
				gameState = GameState::Level2;
			}
			break;

		case Level2:
			drawLevel();
			if (isNextLevel == true) {
				gameState = GameState::EndGame;
			}
			break;

		case EndGame:
			std::cout << "End Of State Machine!" << std::endl;
			break;
		default:
			break;
		}





		csdl_setup->End();

		cap_framerate(starting_tick);
	}
}




void Game::drawLevel()
{
	background->Draw();
	ground->Draw();

	if (isBirdFlying == false) {
		drawSlingshot(birdObj[currentBird]->m_birdBody, physics->slingshotBody, rubberA);
	}

	drawWithPhysics(physics->slingshotBody, slingshotBox, 0, 0);

	for (int i = 0; i < birdObj.size(); i++)
	{
		if (*(int*)birdObj[i]->m_birdBody->GetUserData() == pigDead) {
			birdObj[i]->m_birdBody->SetActive(false);
		}
		if (birdObj[i]->m_birdBody->IsActive()) {
			//drawWithPhysics(birdObj[i]->m_birdBody, birdObj[i]->m_birdSprite, 0, 0);
			drawWithPhysicsAndAnim(birdObj[i]->m_birdBody, birdObj[i]->m_birdSpriteAnimation, 0, 0);
			birdObj[i]->m_birdSpriteAnimation->PlayAnimation(0, 1, 500);
		}
	}

	for (int i = 0; i < pigObj.size(); i++)
	{
		if (pigObj[i]->m_pigBody->IsActive() && (*(int*)pigObj[i]->m_pigBody->GetUserData() == pigDead)) {
			pigObj[i]->m_pigBody->SetActive(false);
			std::cout << "Inside PigSetActive(false)" << std::endl;
			worldbodycount--;
			Mix_PlayChannel(-1, csdl_setup->pigcollide, 0);
			score += 50;
		}
		if (pigObj[i]->m_pigBody->IsActive()) {
			drawWithPhysics(pigObj[i]->m_pigBody, pigObj[i]->m_pigSprite, 0, 0);
		}
	}

	for (int i = 0; i < pigWallObj.size(); i++) {
		drawWithPhysics(pigWallObj[i]->m_pigWallBody, pigWallObj[i]->m_pigWallSprite, (25 - pigWallObj[i]->m_w), (25 - pigWallObj[i]->m_h));
	}

	physics->world->Step(timestep, velocityiterations, positioniterations);



	if (!(birdObj[currentBird]->m_birdBody->IsAwake()) && isBirdFlying == true) {
		bool hasEverythingStopped = false;
		int currentbodycount = 0;
		for (b2Body* b = physics->world->GetBodyList(); b; b = b->GetNext())
		{
			if (!(b->IsAwake())) {
				currentbodycount++;
			}
		}

		if (worldbodycount == currentbodycount) {
			hasEverythingStopped = true;
		}


		if (currentBird < maxBirds) {

			if (hasEverythingStopped == true) {
				birdObj[currentBird]->m_birdBody->SetUserData(&pigDead);
				worldbodycount--;
				currentBird++;
				isBirdFlying = false;
				hasEverythingStopped = false;
			}

		}
		else {
			std::cout << "Game Over! \nScore: " << score << std::endl;
			resetLevel();
		}
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

void Game::drawWithPhysicsAndAnim(b2Body * currBody, Sprite * currSprite, float xCorrection, float yCorrection)
{
	b2Vec2 temp = currBody->GetPosition();
	temp.x += xCorrection * P2M;
	temp.y += yCorrection * P2M;
	float tempAngle = 0 + (currBody->GetAngle() * RADTODEG);
	currSprite->DrawAnimation(temp, tempAngle);
}



void Game::resetLevel()
{
	isButtonDown = false;
	isBirdFlying = false;
	loadNextBird = false;
	currentBird = 0;
	score = 0;
	worldbodycount = 0;
	pigObj.clear();
	birdObj.clear();
	pigWallObj.clear();

	currentLvl++;
	isNextLevel = true;
}

void Game::loadNextLevel()
{

	background = new Sprite(csdl_setup->GetRenderer(), "level" + std::to_string(currentLvl) + "bgn.png", 0, 0, ScreenWidth, ScreenHeight);

	ground = new Sprite(csdl_setup->GetRenderer(), "ground.png", 0, ScreenHeight - 200, ScreenWidth, 1);
	slingshotBox = new Sprite(csdl_setup->GetRenderer(), "ground.png", 700, 700, 25, 25);
	rubberA = new Sprite(csdl_setup->GetRenderer(), "sling.png", 0, 0, 100, 5);

	physics = new BoxPhysics();

	loadFromFile();

	maxBirds = birdObj.size() - 1;

	/*for (int i = 0; i <= maxBirds; i++)
	{
		birdObj.push_back(new Birds(*physics->world, csdl_setup, 400, 400));
	}*/

	//physics->createRopeJoint(birdObj[0]->m_birdBody, physics->slingshotBody);

	/*for (int i = 0; i < 3; i++)
	{
		pigObj.push_back(new Pigs(*physics->world, csdl_setup, 950 + i * 50, 600));
	}*/

	/*pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 900, 600, 10, 70));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 1000, 600, 10, 70));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 950, 520, 100, 10));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 900, 460, 10, 70));
	pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, 1000, 460, 10, 70));*/
}

void Game::loadFromFile()
{
	std::ifstream loadedFile("config/level" + std::to_string(currentLvl) + ".txt");
	std::string line;

	enum ObjectType
	{
		TypeNone,
		TypeBird,
		TypePig,
		TypePigWall
	};

	int currentType = TypeNone;

	if (loadedFile.is_open()) {
		while (loadedFile.good()) {
			std::getline(loadedFile, line);

			if (line == "---===Begin_Birds===---") {
				currentType = TypeBird;
			}
			else if (line == "---===End_Birds===---") {
				currentType = TypeNone;
			}

			else if (line == "---===Begin_Pigs===---") {
				currentType = TypePig;
			}
			else if (line == "---===End_Pigs===---") {
				currentType = TypeNone;
			}
			else if (line == "---===Begin_PigWall===---") {
				currentType = TypePigWall;
			}
			else if (line == "---===End_PigWall===---") {
				currentType = TypeNone;
			}

			else {
				if (currentType == TypeBird) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;

					while (iss) {
						std::string word;
						iss >> word;
						if (word == "x:") {
							iss >> TempX;
						}
						if (word == "y:") {
							iss >> TempY;
							birdObj.push_back(new Birds(*physics->world, csdl_setup, TempX, TempY));
						}
					}
				}

				else if (currentType == TypePig) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;

					while (iss) {
						std::string word;
						iss >> word;
						if (word == "x:") {
							iss >> TempX;
						}
						if (word == "y:") {
							iss >> TempY;

							pigObj.push_back(new Pigs(*physics->world, csdl_setup, TempX, TempY));
							//std::cout << "X is " << TempX << std::endl;
							//std::cout << "Y is " << TempY << std::endl;
						}
					}
				}

				else if (currentType == TypePigWall) {
					std::cout << line << std::endl;
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					int TempW = 0;
					int TempH = 0;

					while (iss) {
						std::string word;
						iss >> word;
						if (word == "x:") {
							iss >> TempX;
						}
						if (word == "y:") {
							iss >> TempY;
						}
						if (word == "w:") {
							iss >> TempW;
						}
						if (word == "h:") {
							iss >> TempH;
							pigWallObj.push_back(new PigWalls(*physics->world, csdl_setup, TempX, TempY, TempW, TempH));
						}
					}
				}
			}
		}
	}

	else {
		std::cout << "File could not be open: level0.txt" << std::endl;
	}

	for (b2Body* b = physics->world->GetBodyList(); b; b = b->GetNext())
	{
		worldbodycount++;
	}

	worldbodycount -= 4;
	std::cout << worldbodycount << std::endl;
}

void Game::drawSlingshot(b2Body * birdBody, b2Body * slingbody, Sprite * rubberband)
{
	b2Vec2 birdPos = birdBody->GetWorldCenter();
	birdPos.x += 0.25;
	birdPos.y += 0.25;
	b2Vec2 slingPos = slingbody->GetWorldCenter();
	slingPos.x += 0.25;
	slingPos.y += 0.25;
	b2Vec2 posToDraw = b2Vec2((birdPos.x + slingPos.x) / 2, (birdPos.y + slingPos.y) / 2);
	double angle = atan2(birdPos.y - slingPos.y, birdPos.x - slingPos.x) * 180 / M_PI;
	rubberband->DrawSling(birdPos, slingPos, angle);
}
