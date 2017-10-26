#include "Window.h"
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>

Window::Window(const string &title, int width, int height) : _title(title), _width(width), _height(height)
{
	_closed = !init();
	
}

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Failed to initialize SDL. \n";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		cerr << "Failed to initialize SDL_image. \n";
		return false;
	}

	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0
	);

	if (_window == nullptr) {
		cerr << "Failed to create window. \n";
		return 0;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == nullptr){
		cerr << "Failed to create renderer. \n";
		return 0;
	}

	return true;
	// c_str() - to convert in a C string
}

void Window::pollEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		
		switch (event.type) {
		case SDL_QUIT:
				_closed = true;
				break;
		
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				_closed = true;
				break;
			}

			
		/*case SDL_MOUSEMOTION:
				cout << event.motion.x << ", " << event.motion.y << '\n';
				break;
			*/
		
		case SDL_MOUSEBUTTONDOWN:
			while (((event.motion.x <= 167) && (event.motion.x >= 47)) && ((event.motion.y <= 530) && (event.motion.y >= 470))){
			cout << "You clicked the PREVIOUS botton! \n";
			break;
			}

			while (((event.motion.x <= 853) && (event.motion.x >= 733)) && ((event.motion.y <= 530) && (event.motion.y >= 470))){
			cout << "You clicked the NEXT botton! \n";
			break;
		}

		default: 
				break;
		}
	
	}
}

void Window::clear() const{
	SDL_RenderPresent(_renderer); //Presents the color on the screen
	SDL_SetRenderDrawColor(_renderer, 255, 248, 220, 255);
	SDL_RenderClear(_renderer);	  //Put the color
}