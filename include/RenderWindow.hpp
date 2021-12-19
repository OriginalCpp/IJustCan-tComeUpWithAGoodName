#pragma once
#include "GameObject.hpp"
#include <SDL.h>

class RenderWindow 
{
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	RenderWindow();
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Renderer* getRenderer();
	void render(GameObject* p_object);
	void display();
	void clear();
	void cleanup();
};