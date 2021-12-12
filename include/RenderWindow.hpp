#pragma once
#include "GameObject.hpp"
#include <SDL.h>

class RenderWindow {
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	void cleanup();
	void clear();
	SDL_Renderer* getRenderer();
	void render(GameObject* p_object);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
