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
	piggyShot = new Sprite(csdl_setup->GetRenderer(), "Scores.png", 0, 0, 200, 115);

	for (int i = 0; i < 10; i++)
	{
		scoreVector.push_back(new Sprite(csdl_setup->GetRenderer(), "images/ScoreSeparate/score" + std::to_string(i) + ".png", 0, 0, 40, 60));
	}

	/*physics = new BoxPhysics();
	loadFromFile();*/

	gameState = GameState::MainMenu;

	/*if (Mix_PlayMusic(csdl_setup->bgm, -1) == -1) {
		std::cout << "Mix_PlayMusic Error: " << Mix_GetError() << std::endl;
	}*/
}


Game::~Game()
{
	delete csdl_setup;
}

void Game::GameLoop()
{
	while (!quit &&csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		if (gameState == MainMenu || isGameOver == true) {

			switch (csdl_setup->GetMainEvent()->type)
			{
			case SDL_MOUSEBUTTONDOWN:
			{
				if (isButtonDown == false) {
					isButtonDown = true;
					//Mix_PlayChannel(-1, csdl_setup->rubberband, 0);
					int x = csdl_setup->GetMainEvent()->button.x;
					int y = csdl_setup->GetMainEvent()->button.y;
					std::cout << "X: " << x;
					std::cout << " Y: " << y << std::endl;
					if ((x > exitButton->rect.x & x < exitButton->rect.x + exitButton->rect.w) && (y > exitButton->rect.y & y < exitButton->rect.y + exitButton->rect.h)) {
						gameState = GameState::EndGame;
					}
					/*if ((x > 1220 & x < 1380) & (y > 718 & y < 836)) {
					std::cout << "You`ve clicked on the main Options..." << std::endl;
					}*/
					if ((x > playButton->rect.x && x < playButton->rect.x + playButton->rect.w) && (y > playButton->rect.y & y < playButton->rect.y + playButton->rect.h))
					{
						startGame = true;

					}
				}

				break;
			}

			case SDL_MOUSEBUTTONUP: {
				if (isButtonDown == true) {
					isButtonDown = false;
					if (startGame == true) {
						gameState = GameState::Level1;
						loadNextLevel();
						isNextLevel = false;
						isButtonDown = false;
						startGame = false;
					}
				}
			}
			default:
				break;

			}
		}

		else if (gameState != MainMenu && gameState != EndGame && restrictUserInput == false)
		{
			if (isNextLevel == true && gameState != EndGame) {
				loadNextLevel();
				isNextLevel = false;
			}


			if (physics->ropeJoint == NULL && isBirdFlying == false) {
				physics->createRopeJoint(birdObj[currentBird]->m_birdBody, physics->slingshotBody);
				birdObj[currentBird]->m_birdBody->SetTransform(b2Vec2(4.8f, 5.0f), birdObj[currentBird]->m_birdBody->GetAngle());
			}


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
					/*int maxX;
					int maxY;
					if (std::abs(((physics->slingshotBody->GetPosition().x *M2P)) - x) < 200) {
						maxX = x;
					}
					if (std::abs(((physics->slingshotBody->GetPosition().y *M2P)) - y) < 200) {
						maxY = y;
					}

					//std::cout << "X: " << x;
					//std::cout << " Y: " << y << std::endl;
					if (x < maxX) {
						x = maxX;
					}*/

					if (x < 350) x = 350;
					if (x > 500) x = 500;
					if (y > 650) y = 650;
					if (y < 400) y = 400;
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
					
					if (physics->ropeJoint != NULL) {
						physics->world->DestroyJoint(physics->ropeJoint);
						physics->ropeJoint = NULL;
					}
					b2Vec2 birdLastPos = birdObj[currentBird]->m_birdBody->GetPosition();
					//b2Vec2 birdLastPos = physics->birdVector[0]->GetPosition();
					b2Vec2 wallPos = physics->slingshotBody->GetPosition();

					

					b2Vec2 forceToApply = b2Vec2(((physics->slingshotBody->GetPosition().x - birdLastPos.x) * P2M), ((physics->slingshotBody->GetPosition().y - birdLastPos.y)*P2M));
					forceToApply.x *= 150;
					forceToApply.y *= 150;
					std::cout << "Xforce: " << forceToApply.x << " Yforce: " << forceToApply.y << std::endl;



					birdObj[currentBird]->m_birdBody->ApplyLinearImpulse(forceToApply, birdObj[currentBird]->m_birdBody->GetWorldCenter(), true);

					Mix_PlayChannel(-1, csdl_setup->birdflying, 0);

					//physics->birdVector[0]->ApplyLinearImpulse(forceToApply, physics->birdVector[0]->GetWorldCenter(), true);
					isBirdFlying = true;
					restrictUserInput = true;
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
			drawMenu();
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
			quit = true;
			//delete csdl_setup;
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
	//DrawScore();
	slingshotB->Draw();
	if (isBirdFlying == false) {
		drawSlingshot(birdObj[currentBird]->m_birdBody, physics->slingshotBody, rubberA);
		drawLeftSlingshot(birdObj[currentBird]->m_birdBody, slingshotA, rubberB);
	}


	for (int i = 0; i < birdObj.size(); i++)
	{
		if (*(int*)birdObj[i]->m_birdBody->GetUserData() == userDataDead) {
			birdObj[i]->m_birdBody->SetActive(false);
		}
		if (birdObj[i]->m_birdBody->IsActive()) {
			//drawWithPhysics(birdObj[i]->m_birdBody, birdObj[i]->m_birdSprite, 0, 0);
			drawWithPhysicsAndAnim(birdObj[i]->m_birdBody, birdObj[i]->m_birdSpriteAnimation, 0, 0);
			birdObj[i]->m_birdSpriteAnimation->PlayAnimation(0, 1, 500);
		}
	}

	slingshotA->Draw();

	for (int i = 0; i < pigObj.size(); i++)
	{
		
		if (pigObj[i]->m_pigBody->IsActive() && (*(int*)pigObj[i]->m_pigBody->GetUserData() == userDataPigDying)) {
			pigtemp = b2Vec2((pigObj[i]->m_pigBody->GetPosition().x) - 1.8f, (pigObj[i]->m_pigBody->GetPosition().y) - 1.6f);
			pigObj[i]->m_pigBody->SetActive(false);
			std::cout << "Inside PigSetActive(false)" << std::endl;
			worldbodycount--;
			pigsKilled++;
			
			Mix_PlayChannel(-1, csdl_setup->pigcollide, 0);
			score += 5000;
			pigScoreStart_tick = SDL_GetTicks() + 750;

		}
		if (!pigObj[i]->m_pigBody->IsActive() && pigScoreStart_tick > SDL_GetTicks() && (*(int*)pigObj[i]->m_pigBody->GetUserData() == userDataPigDying)) {
			piggyShot->Draw(pigtemp);
			drawWithPhysicsAndAnim(pigObj[i]->m_pigBody, pigObj[i]->m_pigDeathAnimation, 0, 0);
			pigObj[i]->m_pigDeathAnimation->PlayAnimation(0, 2, 250);
		}

		if (!pigObj[i]->m_pigBody->IsActive() && pigScoreStart_tick < SDL_GetTicks() && (*(int*)pigObj[i]->m_pigBody->GetUserData() == userDataPigDying)) {
			pigObj[i]->m_pigBody->SetUserData(&userDataDead);
		}


		if (pigObj[i]->m_pigBody->IsActive()) {
			//drawWithPhysics(pigObj[i]->m_pigBody, pigObj[i]->m_pigSprite, 0, 0);
			drawWithPhysicsAndAnim(pigObj[i]->m_pigBody, pigObj[i]->m_pigIdleAnimation, 0, 0);
			pigObj[i]->m_pigIdleAnimation->PlayAnimation(0, 1, 500);
		}
	}

	for (int i = 0; i < pigWallObj.size(); i++) {
		drawWithPhysics(pigWallObj[i]->m_pigWallBody, pigWallObj[i]->m_pigWallSprite, (25 - pigWallObj[i]->m_w), (25 - pigWallObj[i]->m_h));
	}

	physics->world->Step(timestep, velocityiterations, positioniterations);



	if (!(birdObj[currentBird]->m_birdBody->IsAwake()) && isBirdFlying == true ) {
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


		if (currentBird < maxBirds && pigsKilled <= maxPigs) {

			if (hasEverythingStopped == true) {
				birdObj[currentBird]->m_birdBody->SetUserData(&userDataDead);
				worldbodycount--;
				currentBird++;
				isBirdFlying = false;
				restrictUserInput = false;
				hasEverythingStopped = false;
			}

		}
		else {
			if (isGameOver == false) {
				isGameOver = true;
				restrictUserInput = false;

				//std::cout << "Game Over! \nScore: " << score << std::endl;
				gameOver = new Sprite(csdl_setup->GetRenderer(), "gameOver.png", 550, 150, 400, 400);
				replayButton = new Sprite(csdl_setup->GetRenderer(), "replayButton.png", 600, 500, 300, 100);
				//ttfScore = new Sprite(csdl_setup->GetRenderer(), std::to_string(score), ScreenWidth / 2, ScreenHeight / 2);
			}
			gameOver->Draw();
			replayButton->Draw();
			DrawScore();
			//ttfScore->Draw();

			//while (isGameOver=true)
			//{
			switch (csdl_setup->GetMainEvent()->type)
			{
			case SDL_MOUSEBUTTONUP:
			{
				if (isButtonDown == true) {
					isButtonDown = false;
					//Mix_PlayChannel(-1, csdl_setup->rubberband, 0);
					int x = csdl_setup->GetMainEvent()->button.x;
					int y = csdl_setup->GetMainEvent()->button.y;
					std::cout << "X: " << x;
					std::cout << " Y: " << y << std::endl;
					if ((x > 600 & x < 1100) & (y > 500 & y < 600))
					{
						resetLevel();
						isGameOver = false;
					}
				}
				break;
			}

			default:
				break;


			}
			//}
			//gameState = GameState::MainMenu;
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
	isScoreStored = false;

	currentBird = 0;
	score = 0;
	worldbodycount = 0;
	pigsKilled = 0;

	pigObj.clear();
	birdObj.clear();
	pigWallObj.clear();
	scoreDigits.clear();

	currentLvl++;
	isNextLevel = true;
}

void Game::loadNextLevel()
{

	background = new Sprite(csdl_setup->GetRenderer(), "level" + std::to_string(currentLvl) + "bgn.png", 0, 0, ScreenWidth, ScreenHeight);

	ground = new Sprite(csdl_setup->GetRenderer(), "ground.png", 0, ScreenHeight - 200, ScreenWidth, 1);
	slingshotA = new Sprite(csdl_setup->GetRenderer(), "images/SlingA.png", 470, 490, 43, 125);
	slingshotB = new Sprite(csdl_setup->GetRenderer(), "images/SlingB.png", 500, 500, 38, 198);
	rubberA = new Sprite(csdl_setup->GetRenderer(), "images/sling.png", 0, 0, 100, 5);
	rubberB = new Sprite(csdl_setup->GetRenderer(), "images/sling.png", 0, 0, 100, 5);


	physics = new BoxPhysics();

	loadFromFile();

	maxBirds = birdObj.size() - 1;
	maxPigs = pigObj.size() - 1;
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
	double angle = atan2(birdPos.y - slingPos.y, birdPos.x - slingPos.x) * 180 / M_PI;
	rubberband->DrawSling(birdPos, slingPos, angle);
}

void Game::drawLeftSlingshot(b2Body * birdBody, Sprite * leftSprite, Sprite * rubberband)
{
	b2Vec2 birdPos = birdBody->GetWorldCenter();
	birdPos.x += 0.25;
	birdPos.y += 0.25;
	b2Vec2 leftSpritePos = b2Vec2((leftSprite->rect.x + 17)*P2M, (leftSprite->rect.y + 40)*P2M);
	double angle = atan2(birdPos.y - leftSpritePos.y, birdPos.x - leftSpritePos.x) * 180 / M_PI;
	rubberband->DrawSling(birdPos, leftSpritePos, angle);
}


void Game::drawMenu()
{
	if (isMenuImageLoaded == false) {
		isMenuImageLoaded = true;
		background = new Sprite(csdl_setup->GetRenderer(), "images/MainMenu/MainMenuButtonless.png", 0, 0, ScreenWidth, ScreenHeight);
		playButton = new Sprite(csdl_setup->GetRenderer(), "images/MainMenu/PlayButton.png", 1200, 600, 160, 120);
		exitButton = new Sprite(csdl_setup->GetRenderer(), "images/MainMenu/ExitButton.png", 200, 700, 160, 120);
	}
	background->Draw();
	playButton->Draw();
	exitButton->Draw();

}

void Game::getScoreVector() {
	while (score > 0 && isScoreStored == false) {
		scoreDigits.push_back(score % 10);
		score /= 10;
	}
	std::reverse(scoreDigits.begin(), scoreDigits.end());
}

void Game::DrawScore() {

	if (isScoreStored == false) {
		getScoreVector();
		isScoreStored = true;
	}
	for (int i = 0; i < scoreDigits.size(); i++)
	{
		scoreVector[scoreDigits[i]]->Draw(10 + i * 40 , 0);
	}
}

