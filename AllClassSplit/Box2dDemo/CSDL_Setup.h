#pragma once
#include "SDL.h"
class CSDL_Setup
{
public:
	CSDL_Setup(bool* quit, int ScreenWidth, int SCreenHeight);
	~CSDL_Setup();

	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();

	void Begin();
	void End();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
};

