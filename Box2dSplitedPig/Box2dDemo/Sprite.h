#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Box2D\Box2D.h"
#include "BoxPhysics.h"
#include "Pigs.h"
#include <iostream>
class Sprite
{
public:
	Sprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h);
	~Sprite(void);

	void Draw();
	void Draw(b2Vec2 newPos);
	void Draw(b2Vec2 newPos, float angle);

private:
	SDL_Texture* image;
	SDL_Rect rect;

	SDL_Renderer* renderer;
};

