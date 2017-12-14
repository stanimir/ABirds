#include "CSDL_Setup.h"
#include <iostream>


CSDL_Setup::CSDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight)
{

	SDL_Init(SDL_INIT_EVERYTHING);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Error: " << Mix_GetError() << std::endl;
	}

	bgm = Mix_LoadMUS("theme.ogg");
	rubberband = Mix_LoadWAV("slingshotstr.wav");

	window = NULL;
	window = SDL_CreateWindow("ABirds", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window couldn't be created" << std::endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();
}


CSDL_Setup::~CSDL_Setup(void)
{
	Mix_FreeChunk(rubberband);
	Mix_FreeMusic(bgm);

	Mix_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_Setup::GetMainEvent()
{
	return mainEvent;
}

void CSDL_Setup::Begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}

void CSDL_Setup::End()
{
	SDL_RenderPresent(renderer);
}

