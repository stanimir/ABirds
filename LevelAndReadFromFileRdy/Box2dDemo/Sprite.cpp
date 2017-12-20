#include "Sprite.h"

const float M2P = 100;
const float P2M = 1 / M2P;
const float DEGTORAD = 0.0174532925199432957f;
const float RADTODEG = 57.295779513082320876f;

Sprite::Sprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h)
{
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());

	if (image == NULL)
	{
		std::cout << "Couldn't Load " << FilePath.c_str() << std::endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}


Sprite::~Sprite(void)
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw()
{
	SDL_RenderCopy(renderer, image, NULL, &rect);
}

void Sprite::Draw(b2Vec2 newPos)
{
	SDL_Rect temp;
	temp.x = newPos.x * 100;
	temp.y = newPos.y * 100;
	temp.w = rect.w * 2;
	temp.h = rect.h * 2;
	SDL_RenderCopy(renderer, image, NULL, &temp);
}

void Sprite::Draw(b2Vec2 newPos, float angle)
{
	SDL_Rect temp;
	temp.x = newPos.x * M2P;
	temp.y = newPos.y * M2P;
	temp.w = rect.w * 2;
	temp.h = rect.h * 2;
	SDL_RenderCopyEx(renderer, image, NULL, &temp, angle, NULL, SDL_FLIP_NONE);
}

void Sprite::DrawSling(b2Vec2 birdPos, b2Vec2 slingPos, float angle)
{
	double distanceBetween = sqrt(pow((slingPos.x - birdPos.x), 2) + pow((slingPos.y - birdPos.y), 2));
	float angle2 = angle;
	//std::cout << "Distance: " << distanceBetween * M2P << std::endl;

	rect.w = (distanceBetween * M2P) / 2;

	SDL_Point rotatePoint;
	rotatePoint.x = slingPos.x;
	rotatePoint.y = slingPos.y;

	SDL_Rect temp;
	temp.x = slingPos.x  * M2P;
	temp.y = (slingPos.y + 0.1) * M2P;
	temp.w = rect.w * 2;
	temp.h = rect.h * 2;
	SDL_RenderCopyEx(renderer, image, NULL, &temp, angle, &rotatePoint, SDL_FLIP_NONE);

	SDL_Rect temp1;
	temp1.x = (slingPos.x)  * M2P;
	temp1.y = (slingPos.y - 0.1) * M2P;
	temp1.w = rect.w * 2;
	temp1.h = rect.h * 2;
	angle2 -= 4;
	SDL_RenderCopyEx(renderer, image, NULL, &temp1, angle2, &rotatePoint, SDL_FLIP_NONE);
}



