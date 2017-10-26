#include "SDL.h"
#include "SDL_image.h"
#include "rect.h"
#include <iostream>

#include "Window.h"

using namespace std; 

int main(int argc, char* argv[]){
	
	Window window("Angry Birds", 900, 563);

	Rect Button1(window, 120, 60, 47, 470 ,"res/prevButton.png");
	Rect Button2(window, 120, 60, 733, 470, "res/nextButton.png");

	while (!window.isClosed()) {
		Button1.draw();
		Button2.draw();
		window.pollEvents();
		window.clear();
	
	}
	return 0;

}