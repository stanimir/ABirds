#pragma once

#include <string>
#include <SDL.h>

using namespace std;

class Window
{

public:
	Window(const string &title, int width, int height);
	Window();
	~Window();

	inline bool isClosed() const {
		return _closed;
	}
	// Detect and Do Something that was detect
	void pollEvents();
	void clear() const;

private: 
	bool init();

private:
	string _title;
	int _width = 900;
	int _height = 563;

	bool _closed = false;
	SDL_Window *_window = nullptr;

protected:
	SDL_Renderer *_renderer = nullptr;
};


