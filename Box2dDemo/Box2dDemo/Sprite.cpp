#include "Sprite.h"



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
	temp.x = newPos.x*100;
	temp.y = newPos.y*100;
	temp.w = rect.w;
	temp.h = rect.h;
	//Draw();
	SDL_RenderCopy(renderer, image, NULL, &temp);
}


