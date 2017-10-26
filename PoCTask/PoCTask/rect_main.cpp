#include "rect.h"
#include "SDL_image.h"
#include <string>
#include <iostream>


Rect::Rect(const Window &window, int w, int h, int x, int y, int r, int g, int b, int a) :
	Window(window), _w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{
}

Rect::Rect(const Window &window, int w, int h, int x, int y, const string &image_path) :
	Window(window), _w(w), _h(h), _x(x), _y(y)
{
	auto surface = IMG_Load(image_path.c_str());

	if (!surface) {
		cerr << "Failed to create surface! \n";
	}

	_button_texture = SDL_CreateTextureFromSurface(_renderer, surface);

	if (!_button_texture) {
		cerr << "Failed to create texture! \n";
	}
	SDL_FreeSurface(surface);
}

Rect::~Rect() {
	SDL_DestroyTexture(_button_texture);
}

void Rect::draw() const {
	SDL_Rect Button;

	Button.w = _w;
	Button.h = _h;
	Button.x = _x;
	Button.y = _y;
	
	if (_button_texture) {
		SDL_RenderCopy(_renderer, _button_texture, nullptr, &Button);
	}
	else {
	
	SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
	SDL_RenderFillRect(_renderer, &Button);
	}
		//(_width / 2) - (Button1.w / 2)
		//(_height / 2) - (Button1.h / 2);
		//If we want to center the Button on the screen
	
}